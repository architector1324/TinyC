#ifndef CPT
#define CPT

#include <gmp.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "vec.h"
#include "tup.h"
#include "arr.h"

#define CPT_RSA_MAX_MSG_LEN 1024
SLICE(uint8_t)
MICRO_VECTOR_CUSTOM(uint8_t, CPT_RSA_MAX_MSG_LEN)

ARRAY(uint8_t, 512)
TUPLE(arr(uint8_t, 512), arr(uint8_t, 512))


/////////////////////////////////
//            HASH             //
/////////////////////////////////

// sha256

// md5

/////////////////////////////////
//             RSA             //
/////////////////////////////////
tup(arr(uint8_t, 512), arr(uint8_t, 512)) cpt_gen_keys() {
    // generate random primes p, q
    mpz_t p, q;
    gmp_randstate_t rand;

    gmp_randinit_default(rand);
    mpz_init(p);
    mpz_init(q);

    mpz_urandomb(p, rand, 1024);
    mpz_urandomb(q, rand, 1024);

    mpz_nextprime(p, p);
    mpz_nextprime(q, q);
    // gmp_printf("q=%Zd\np=%Zd\n", p, q);

    // generate n
    mpz_t n, e;
    mpz_init(n);
    mpz_init(e);

    mpz_mul(n, p, q);
    mpz_init_set_ui(e, 65537);
    // gmp_printf("n=%Zd\n", n);

    // generate phi(n)
    mpz_t p1, q1, phi_n;
    mpz_init(p1);
    mpz_init(q1);
    mpz_init(phi_n);

    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, q, 1);
    mpz_mul(phi_n, p1, q1);

    // generate d
    mpz_t d;
    mpz_init(d);
    mpz_invert(d, e, phi_n);
    // gmp_printf("d=%Zd\n", d);

    // encode keys: pub = {e,n}, priv = {d,n}
    arr(uint8_t, 512) pub = arr_init(uint8_t, 512)();
    mpz_export(pub.data, NULL, -1, sizeof(uint8_t), 1, 0, e);
    mpz_export(pub.data + 256, NULL, -1, sizeof(uint8_t), 1, 0, n);

    arr(uint8_t, 512) priv = arr_init(uint8_t, 512)();
    mpz_export(priv.data, NULL, -1, sizeof(uint8_t), 1, 0, d);
    mpz_export(priv.data + 256, NULL, -1, sizeof(uint8_t), 1, 0, n);

    // free
    mpz_clear(d);
    mpz_clear(p1);
    mpz_clear(q1);
    mpz_clear(phi_n);
    mpz_clear(e);
    mpz_clear(n);
    mpz_clear(p);
    mpz_clear(q);
    gmp_randclear(rand);

    return (tup(arr(uint8_t, 512), arr(uint8_t, 512))){pub, priv};
}

vec_micro(uint8_t) cpt_rsa_encrypt(slc(uint8_t) data, const arr(uint8_t, 512)* pub) {
    // convert msg to m and pub key to n
    mpz_t m, e, n;
    mpz_init(m);
    mpz_init(e);
    mpz_init(n);

    mpz_import(m, data.size, -1, sizeof(uint8_t), 1, 0, data.data);
    mpz_import(e, 256, -1, sizeof(uint8_t), 1, 0, pub->data);
    mpz_import(n, 256, -1, sizeof(uint8_t), 1, 0, pub->data + 256);

    // gmp_printf("m=%Zd\n", m);
    // gmp_printf("e=%Zd\n", e);
    // gmp_printf("n=%Zd\n", n);

    // encrypt msg
    mpz_t c;
    mpz_init(c);
    mpz_powm(c, m, e, n);
    // gmp_printf("c=%Zd\n", c);

    // encode data
    vec_micro(uint8_t) res = vec_micro_init(uint8_t)();
    size_t size;

    mpz_export(res.data, &size, -1, sizeof(uint8_t), 1, 0, c);
    res.size = size;

    // free
    mpz_clear(c);
    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(m);

    return res;
}

vec_micro(uint8_t) cpt_rsa_decrypt(slc(uint8_t) data, const arr(uint8_t, 512)* priv) {
    // convert priv to {d,n} and data to c
    mpz_t d, n, c;
    mpz_init(d);
    mpz_init(n);
    mpz_init(c);

    mpz_import(d, 256, -1, sizeof(uint8_t), 1, 0, priv->data);
    mpz_import(n, 256, -1, sizeof(uint8_t), 1, 0, priv->data + 256);
    mpz_import(c, data.size, -1, sizeof(uint8_t), 1, 0, data.data);

    // gmp_printf("d=%Zd\n", d);
    // gmp_printf("n=%Zd\n", n);
    // gmp_printf("c=%Zd\n", c);

    // decypt msg
    mpz_t m;
    mpz_init(m);
    mpz_powm(m, c, d, n);
    // gmp_printf("m=%Zd\n", m);

    // encode data
    vec_micro(uint8_t) res = vec_micro_init(uint8_t)();
    size_t count =  mpz_sizeinbase(m, 2) / 8;

    mpz_export(res.data, NULL, -1, sizeof(uint8_t), 1, 0, m);
    res.size = count;

    // free
    mpz_clear(m);
    mpz_clear(c);
    mpz_clear(n);
    mpz_clear(d);

    return res;
}

/////////////////////////////////
//        DIGITAL SIGN         //
/////////////////////////////////
ARRAY(uint8_t, 256)

arr(uint8_t, 256) cpt_sign(slc(uint8_t) data, const arr(uint8_t, 512)* priv) {
    vec_micro(uint8_t) sign = cpt_rsa_encrypt(data, priv);

    arr(uint8_t, 256) res = arr_init(uint8_t, 256)();
    memcpy(res.data, sign.data, 256);

    return res;
}

bool cpt_sign_verify(slc(uint8_t) data, const arr(uint8_t, 256)* sign, const arr(uint8_t, 512)* pub) {
    vec_micro(uint8_t) tmp = cpt_rsa_decrypt(sign->slice(sign), pub);
    
    return !memcmp(data.data, tmp.data, data.size);
}

#endif
