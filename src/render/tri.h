#ifndef TRI_H
#define TRI_H

#include <stdint.h>

typedef struct {
    float x, y, z;
} Vec3;

void triangle_fill_halfspace(uint32_t *fb, float *zbuf, int width, int height,
                             Vec3 v0, Vec3 v1, Vec3 v2, uint32_t color);

#endif /* TRI_H */
