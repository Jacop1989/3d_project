#pragma once
/// Bresenham line drawing.
#include <stdint.h>
#include "framebuffer.h"
#include "vec.h"

void line_draw(Framebuffer *fb, Vec3 a, Vec3 b, uint32_t color);
