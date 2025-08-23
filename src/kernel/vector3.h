#ifndef KERNEL_VECTOR3_H
#define KERNEL_VECTOR3_H

#include <cmath>

class Vector3 {
public:
    double x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    Vector3 operator+(const Vector3 &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3 operator-(const Vector3 &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vector3 operator*(double s) const {
        return {x * s, y * s, z * s};
    }

    bool operator==(const Vector3 &other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Vector3 &other) const {
        return !(*this == other);
    }

    double dot(const Vector3 &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 cross(const Vector3 &other) const {
        return {y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x};
    }

    double norm() const {
        return std::sqrt(dot(*this));
    }
};

#endif // KERNEL_VECTOR3_H
