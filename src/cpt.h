#ifndef CPT
#define CPT

#include <gmp.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "chn.h"
#include "tup.h"
#include "arr.h"

#define CPT_RSA_MAX_MSG_LEN 1024
SLICE(uint8_t)
CHAIN(uint8_t)
MICRO_VECTOR_CUSTOM(uint8_t, CPT_RSA_MAX_MSG_LEN)

ARRAY(uint8_t, 512)
TUPLE(arr(uint8_t, 512), arr(uint8_t, 512))


/////////////////////////////////
//            HASH             //
/////////////////////////////////

// sha256
ARRAY(uint8_t, 32)

arr(uint8_t, 32) cpt_sha256(slc(uint8_t) data) {
    arr(uint8_t, 32) res = arr_init(uint8_t, 32)();

    #define rotr(x, n) (x >> n % 32) | (x << (32-n) % 32)
    #define htonll(x) ((((uint64_t)htonl(x)) << 32) + htonl((x) >> 32))

    // init
    static uint32_t h[8] = {
        0x6a09e667,
        0xbb67ae85,
        0x3c6ef372,
        0xa54ff53a,
        0x510e527f,
        0x9b05688c,
        0x1f83d9ab,
        0x5be0cd19
    };

    static uint32_t k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    // prepare msg
    chn(uint8_t) m = chn_init(uint8_t)();

    uint8_t single_bit = 128;
    chn_chain(m, data);
    chn_chain(m, slc_from(uint8_t)(&single_bit, 1));

    size_t k0 = 0;
    while((8 * data.size + 1 + k0) % 512 != 448) k0++;

    vec_micro(uint8_t) zeros = vec_micro_init(uint8_t)();
    zeros.size = (k0 - 7) / 8;
    chn_chain(m, to_slc(zeros));

    uint64_t len = htonll(8 * data.size);
    chn_chain(m, slc_from(uint8_t)((uint8_t*)&len, 8));

    if(m.size % 64 != 0) {
        vec_micro(uint8_t) zeros2 = vec_micro_init(uint8_t)();
        zeros2.size = 64 - m.size % 64;
        chn_chain(m, to_slc(zeros2));
    }

    // process 512-bit blocks
    for(size_t i = 0; i < m.size / 64; i++) {
        uint32_t block[64];
        for(size_t j = 0; j < 64; j++){
            uint8_t _b = chn_at(m, j + i * 64);
            memcpy((uint8_t*)block + j, &_b, 1);
        }

        for(size_t j = 16; j < 64; j++) {
            uint32_t s0 = rotr(block[j - 15], 7) ^ rotr(block[j - 15], 18) ^ (block[j - 15] >> 3);
            uint32_t s1 = rotr(block[j - 2], 17) ^ rotr(block[j - 2], 19) ^ (block[j - 2] >> 10);
            block[j] = block[j - 16] + s0 + block[j - 7] + s1;
        }

        // extra vars
        uint32_t a = h[0];
        uint32_t b = h[1];
        uint32_t c = h[2];
        uint32_t d = h[3];
        uint32_t e = h[4];
        uint32_t f = h[5];
        uint32_t g = h[6];
        uint32_t _h = h[7];

        // work
        for(size_t j = 0; j < 64; j++) {
            uint32_t sig0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
            uint32_t Ma = (a & b) ^ (a & c) ^ (b & c);
            uint32_t t2 = sig0 + Ma;
            uint32_t sig1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
            uint32_t Ch = (e & f) ^ ((~e) & g);
            uint32_t t1 = _h + sig1 + Ch + k[j] + block[j];

            _h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t1;
        }

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
        h[5] += f;
        h[6] += g;
        h[7] += _h;
    }

    // copy to out buffer
    memcpy(res.data, h, 32);

    return res;
}

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
    vec_micro(uint8_t) dec = cpt_rsa_decrypt(sign->slice(sign), pub);
    
    return !memcmp(data.data, dec.data, data.size);
}

#endif
