#include "camera.h"
#include <math.h>

void camera_init(Camera *cam, float yaw, float pitch, float dist, Vec3 target) {
    cam->yaw = yaw;
    cam->pitch = pitch;
    cam->dist = dist;
    cam->target = target;
}

Mat4 camera_view_matrix(const Camera *cam) {
    float cy = cosf(cam->yaw);
    float sy = sinf(cam->yaw);
    float cp = cosf(cam->pitch);
    float sp = sinf(cam->pitch);
    Vec3 eye = {
        cam->target.x + cam->dist * cp * sy,
        cam->target.y + cam->dist * sp,
        cam->target.z + cam->dist * cp * cy
    };
    Vec3 up = {0.0f, 1.0f, 0.0f};
    return mat4_look_at(eye, cam->target, up);
}
