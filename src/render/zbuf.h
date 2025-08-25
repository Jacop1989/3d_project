#ifndef ZBUF_H
#define ZBUF_H

#include <stddef.h>

void zbuf_clear(float *zbuf, size_t width, size_t height, float value);
int zbuf_test_and_write(float *zbuf, size_t width, size_t x, size_t y, float z);

#endif /* ZBUF_H */
