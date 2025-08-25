#include "zbuf.h"

void zbuf_clear(float *zbuf, size_t width, size_t height, float value) {
    size_t total = width * height;
    for (size_t i = 0; i < total; ++i) {
        zbuf[i] = value;
    }
}

int zbuf_test_and_write(float *zbuf, size_t width, size_t x, size_t y, float z) {
    size_t idx = y * width + x;
    if (z < zbuf[idx]) {
        zbuf[idx] = z;
        return 1;
    }
    return 0;
}
