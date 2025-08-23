#ifndef KERNEL_BOOLEAN_H
#define KERNEL_BOOLEAN_H

#include <vector>
#include <algorithm>
#include "vector3.h"

struct Mesh {
    std::vector<Vector3> vertices;
};

Mesh boolean_union(const Mesh &a, const Mesh &b);
Mesh boolean_subtract(const Mesh &a, const Mesh &b);
Mesh boolean_intersect(const Mesh &a, const Mesh &b);

#endif // KERNEL_BOOLEAN_H
