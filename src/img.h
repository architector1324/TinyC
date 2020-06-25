#ifndef IMAGE
#define IMAGE

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <png.h>

// write RGB data to ppm file
bool img_ppm_write(const char* name, uint8_t* data, size_t w, size_t h) {
    FILE* f = fopen(name, "wb");
    if(!f) return true;

    fprintf(f, "P6\n%ld %ld 255\n", w, h);
    for(size_t i = 0; i < w; i++)
        for(size_t j = 0; j < h; j++)
            fprintf(
                f, "%c%c%c",
                data[i + j * w],
                data[i + j * w + 1],
                data[i + j * w + 2]
            );

    fclose(f);
    return false;
}

// write RGBA data to png file
bool img_png_write(const char *name, uint8_t* data, size_t w, size_t h) {
    FILE* f = fopen(name, "wb");
    if(!f) return true;

    // create structs
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png) return true;

    png_infop info = png_create_info_struct(png);
    if(!info) return true;
    if (setjmp(png_jmpbuf(png))) return true;

    // init structs
    png_init_io(png, f);
    png_set_IHDR(
        png, info, w, h, 8, PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(png, info);

    // render
    uint8_t* rows[h];
    for(size_t i = 0; i < h; i++)
        rows[i] = data + i * w * 4;

    png_write_image(png, rows);
    png_write_end(png, NULL);

    // free
    png_destroy_write_struct(&png, &info);
    fclose(f);
    return false;
}

#endif
