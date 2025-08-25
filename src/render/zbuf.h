#pragma once
/// Simple floating point depth buffer.
#include <stddef.h>

typedef struct {
    float *data;
    size_t width;
    size_t height;
} ZBuffer;

int zbuf_init(ZBuffer *zb, size_t width, size_t height);
void zbuf_clear(ZBuffer *zb, float value);
void zbuf_free(ZBuffer *zb);
int zbuf_test_and_write(ZBuffer *zb, size_t x, size_t y, float z);
