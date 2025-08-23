#ifndef KERNEL_MATRIX4_H
#define KERNEL_MATRIX4_H

#include "vector3.h"
#include <array>

class Matrix4 {
public:
    std::array<double, 16> m{}; // row-major

    Matrix4() { setIdentity(); }

    static Matrix4 identity() {
        Matrix4 mat;
        mat.setIdentity();
        return mat;
    }

    void setIdentity() {
        m = {1,0,0,0,
             0,1,0,0,
             0,0,1,0,
             0,0,0,1};
    }

    Matrix4 operator*(const Matrix4 &other) const {
        Matrix4 result;
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                result.m[r*4+c] = 0;
                for (int k = 0; k < 4; ++k) {
                    result.m[r*4+c] += m[r*4+k] * other.m[k*4+c];
                }
            }
        }
        return result;
    }

    Vector3 transformPoint(const Vector3 &v) const {
        double x = m[0]*v.x + m[1]*v.y + m[2]*v.z + m[3];
        double y = m[4]*v.x + m[5]*v.y + m[6]*v.z + m[7];
        double z = m[8]*v.x + m[9]*v.y + m[10]*v.z + m[11];
        double w = m[12]*v.x + m[13]*v.y + m[14]*v.z + m[15];
        if (w != 0 && w != 1) {
            x /= w; y /= w; z /= w;
        }
        return {x, y, z};
    }
};

#endif // KERNEL_MATRIX4_H
