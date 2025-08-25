#include "mat4.h"
#include <math.h>

Mat4 mat4_identity(void) {
    Mat4 m = { .m = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    }};
    return m;
}

Mat4 mat4_mul(Mat4 a, Mat4 b) {
    Mat4 r;
    for (int c = 0; c < 4; ++c) {
        for (int r0 = 0; r0 < 4; ++r0) {
            r.m[c*4 + r0] =
                a.m[0*4 + r0] * b.m[c*4 + 0] +
                a.m[1*4 + r0] * b.m[c*4 + 1] +
                a.m[2*4 + r0] * b.m[c*4 + 2] +
                a.m[3*4 + r0] * b.m[c*4 + 3];
        }
    }
    return r;
}

Vec4 mat4_mul_vec4(Mat4 m, Vec4 v) {
    Vec4 r;
    r.x = m.m[0]*v.x + m.m[4]*v.y + m.m[8]*v.z + m.m[12]*v.w;
    r.y = m.m[1]*v.x + m.m[5]*v.y + m.m[9]*v.z + m.m[13]*v.w;
    r.z = m.m[2]*v.x + m.m[6]*v.y + m.m[10]*v.z + m.m[14]*v.w;
    r.w = m.m[3]*v.x + m.m[7]*v.y + m.m[11]*v.z + m.m[15]*v.w;
    return r;
}

Mat4 mat4_translate(float x, float y, float z) {
    Mat4 m = mat4_identity();
    m.m[12] = x;
    m.m[13] = y;
    m.m[14] = z;
    return m;
}

Mat4 mat4_scale(float x, float y, float z) {
    Mat4 m = { .m = {
        x,    0.0f, 0.0f, 0.0f,
        0.0f, y,    0.0f, 0.0f,
        0.0f, 0.0f, z,    0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    }};
    return m;
}

Mat4 mat4_rotate_x(float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    Mat4 m = mat4_identity();
    m.m[5] = c;  m.m[9] = -s;
    m.m[6] = s;  m.m[10] = c;
    return m;
}

Mat4 mat4_rotate_y(float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    Mat4 m = mat4_identity();
    m.m[0] = c;  m.m[8] = s;
    m.m[2] = -s; m.m[10] = c;
    return m;
}

Mat4 mat4_rotate_z(float angle) {
    float c = cosf(angle);
    float s = sinf(angle);
    Mat4 m = mat4_identity();
    m.m[0] = c;  m.m[4] = -s;
    m.m[1] = s;  m.m[5] = c;
    return m;
}

Mat4 mat4_perspective(float fovy, float aspect, float near_z, float far_z) {
    float f = 1.0f / tanf(fovy * 0.5f);
    Mat4 m = {0};
    m.m[0] = f / aspect;
    m.m[5] = f;
    m.m[10] = (far_z + near_z) / (near_z - far_z);
    m.m[14] = (2.0f * far_z * near_z) / (near_z - far_z);
    m.m[11] = -1.0f;
    return m;
}

Mat4 mat4_look_at(Vec3 eye, Vec3 center, Vec3 up) {
    Vec3 f = vec3_normalize(vec3_sub(center, eye));
    Vec3 s = vec3_normalize(vec3_cross(f, up));
    Vec3 u = vec3_cross(s, f);

    Mat4 m = mat4_identity();
    m.m[0] = s.x; m.m[4] = s.y; m.m[8]  = s.z;
    m.m[1] = u.x; m.m[5] = u.y; m.m[9]  = u.z;
    m.m[2] = -f.x; m.m[6] = -f.y; m.m[10] = -f.z;
    m.m[12] = -vec3_dot(s, eye);
    m.m[13] = -vec3_dot(u, eye);
    m.m[14] = vec3_dot(f, eye);
    return m;
}
