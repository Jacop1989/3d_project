#pragma once
/// Half-space triangle rasterizer with z-buffer.
#include <stdint.h>
#include "vec.h"
#include "framebuffer.h"
#include "zbuf.h"

void tri_fill(Framebuffer *fb, ZBuffer *zb, Vec3 v0, Vec3 v1, Vec3 v2, uint32_t color);
