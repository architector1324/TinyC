#ifndef IMAGE
#define IMAGE

// write argb data to png file
bool img_ppm_write(const char* name, uint8_t* data, size_t w, size_t h) {
    FILE* f = fopen(name, "wb");

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

#endif
