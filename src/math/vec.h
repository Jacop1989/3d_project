#pragma once
/// Basic vector types and operations.
#include <math.h>

typedef struct { float x, y, z; } Vec3;
typedef struct { float x, y, z, w; } Vec4;

static inline Vec3 vec3_add(Vec3 a, Vec3 b){ return (Vec3){a.x+b.x,a.y+b.y,a.z+b.z}; }
static inline Vec3 vec3_sub(Vec3 a, Vec3 b){ return (Vec3){a.x-b.x,a.y-b.y,a.z-b.z}; }
static inline Vec3 vec3_scale(Vec3 v, float s){ return (Vec3){v.x*s,v.y*s,v.z*s}; }
static inline float vec3_dot(Vec3 a, Vec3 b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
static inline Vec3 vec3_cross(Vec3 a, Vec3 b){
    return (Vec3){ a.y*b.z - a.z*b.y,
                   a.z*b.x - a.x*b.z,
                   a.x*b.y - a.y*b.x };
}
static inline Vec3 vec3_normalize(Vec3 v){
    float len = sqrtf(vec3_dot(v,v));
    return len>0 ? vec3_scale(v,1.0f/len) : v;
}

static inline int float_equal(double a, double b, double eps){
    return fabs(a-b) <= eps;
}
