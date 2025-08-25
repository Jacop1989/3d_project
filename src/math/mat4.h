#pragma once
/// 4x4 matrix utilities.
#include "vec.h"

typedef struct { float m[16]; } Mat4;

Mat4 mat4_identity(void);
Mat4 mat4_mul(Mat4 a, Mat4 b);
Vec4 mat4_mul_vec4(Mat4 m, Vec4 v);
Mat4 mat4_translate(float x, float y, float z);
Mat4 mat4_scale(float x, float y, float z);
Mat4 mat4_rotate_x(float angle);
Mat4 mat4_rotate_y(float angle);
Mat4 mat4_rotate_z(float angle);
Mat4 mat4_perspective(float fovy, float aspect, float near_z, float far_z);
Mat4 mat4_look_at(Vec3 eye, Vec3 center, Vec3 up);
