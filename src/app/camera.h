#pragma once
/// Simple orbit camera.
#include "vec.h"
#include "mat4.h"

typedef struct {
    float yaw;
    float pitch;
    float dist;
    Vec3 target;
} Camera;

void camera_init(Camera *cam, float yaw, float pitch, float dist, Vec3 target);
Mat4 camera_view_matrix(const Camera *cam);
