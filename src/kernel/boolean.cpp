#include "boolean.h"

namespace {
    bool contains(const std::vector<Vector3> &verts, const Vector3 &v) {
        return std::find(verts.begin(), verts.end(), v) != verts.end();
    }
}

Mesh boolean_union(const Mesh &a, const Mesh &b) {
    Mesh result;
    result.vertices = a.vertices;
    for (const auto &v : b.vertices) {
        if (!contains(result.vertices, v)) {
            result.vertices.push_back(v);
        }
    }
    return result;
}

Mesh boolean_subtract(const Mesh &a, const Mesh &b) {
    Mesh result;
    for (const auto &v : a.vertices) {
        if (!contains(b.vertices, v)) {
            result.vertices.push_back(v);
        }
    }
    return result;
}

Mesh boolean_intersect(const Mesh &a, const Mesh &b) {
    Mesh result;
    for (const auto &v : a.vertices) {
        if (contains(b.vertices, v)) {
            if (!contains(result.vertices, v)) {
                result.vertices.push_back(v);
            }
        }
    }
    return result;
}
