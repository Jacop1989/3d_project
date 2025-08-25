#ifndef CAMERA_H
#define CAMERA_H

#include "tri.h"
#include "mat4.h"

typedef struct {
    float yaw;
    float pitch;
    float dist;
    Vec3 target;
} Camera;

void camera_init(Camera *cam, float yaw, float pitch, float dist, Vec3 target);
Mat4 camera_view_matrix(const Camera *cam);

#endif /* CAMERA_H */
