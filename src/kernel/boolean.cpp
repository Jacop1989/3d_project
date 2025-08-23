#include "boolean.h"
#include <algorithm>
#include <vector>
#include "vector3.h"

namespace {
    bool contains(const std::vector<Vector3> &verts, const Vector3 &v) {
        return std::find(verts.begin(), verts.end(), v) != verts.end();
    }
}

Mesh boolean_union(const Mesh &a, const Mesh &b) {
    kernel::MeshCpp ac = kernel::to_cpp_mesh(a);
    kernel::MeshCpp bc = kernel::to_cpp_mesh(b);
    kernel::MeshCpp rc;
    rc.vertices = ac.vertices;
    for (const auto &v : bc.vertices) {
        if (!contains(rc.vertices, v)) {
            rc.vertices.push_back(v);
        }
    }
    return kernel::to_c_mesh(rc);
}

Mesh boolean_subtract(const Mesh &a, const Mesh &b) {
    kernel::MeshCpp ac = kernel::to_cpp_mesh(a);
    kernel::MeshCpp bc = kernel::to_cpp_mesh(b);
    kernel::MeshCpp rc;
    for (const auto &v : ac.vertices) {
        if (!contains(bc.vertices, v)) {
            rc.vertices.push_back(v);
        }
    }
    return kernel::to_c_mesh(rc);
}

Mesh boolean_intersect(const Mesh &a, const Mesh &b) {
    kernel::MeshCpp ac = kernel::to_cpp_mesh(a);
    kernel::MeshCpp bc = kernel::to_cpp_mesh(b);
    kernel::MeshCpp rc;
    for (const auto &v : ac.vertices) {
        if (contains(bc.vertices, v)) {
            if (!contains(rc.vertices, v)) {
                rc.vertices.push_back(v);
            }
        }
    }
    return kernel::to_c_mesh(rc);
}
