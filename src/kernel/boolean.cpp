#include "boolean.h"
#include <algorithm>
#include <vector>
#include <cmath>
#include "vector3.h"

namespace {
    constexpr double EPS = 1e-6;

    int find_vertex(const std::vector<Vector3> &verts, const Vector3 &v) {
        for (size_t i = 0; i < verts.size(); ++i) {
            const auto &o = verts[i];
            if (std::fabs(o.x - v.x) < EPS &&
                std::fabs(o.y - v.y) < EPS &&
                std::fabs(o.z - v.z) < EPS) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    bool contains(const std::vector<Vector3> &verts, const Vector3 &v) {
        return find_vertex(verts, v) != -1;
    }

    bool contains(const std::vector<Face> &faces, const Face &f) {
        return std::find_if(faces.begin(), faces.end(), [&](const Face &o) {
            return o.v1 == f.v1 && o.v2 == f.v2 && o.v3 == f.v3;
        }) != faces.end();
    }
}

Mesh boolean_union(const Mesh &a, const Mesh &b) {
    kernel::MeshCpp ac = kernel::to_cpp_mesh(a);
    kernel::MeshCpp bc = kernel::to_cpp_mesh(b);
    kernel::MeshCpp rc;
    rc.vertices = ac.vertices;
    rc.faces = ac.faces;

    std::vector<int> index_map(bc.vertices.size());
    for (size_t i = 0; i < bc.vertices.size(); ++i) {
        int idx = find_vertex(rc.vertices, bc.vertices[i]);
        if (idx == -1) {
            rc.vertices.push_back(bc.vertices[i]);
            idx = static_cast<int>(rc.vertices.size() - 1);
        }
        index_map[i] = idx;
    }

    for (const auto &f : bc.faces) {
        Face mapped{index_map[f.v1], index_map[f.v2], index_map[f.v3]};
        if (!contains(rc.faces, mapped)) {
            rc.faces.push_back(mapped);
        }
    }

    return kernel::to_c_mesh(rc);
}

Mesh boolean_subtract(const Mesh &a, const Mesh &b) {
    kernel::MeshCpp ac = kernel::to_cpp_mesh(a);
    kernel::MeshCpp bc = kernel::to_cpp_mesh(b);
    kernel::MeshCpp rc;
    std::vector<int> index_map(ac.vertices.size(), -1);
    for (size_t i = 0; i < ac.vertices.size(); ++i) {
        if (!contains(bc.vertices, ac.vertices[i])) {
            index_map[i] = static_cast<int>(rc.vertices.size());
            rc.vertices.push_back(ac.vertices[i]);
        }
    }

    for (const auto &f : ac.faces) {
        int v1 = index_map[f.v1];
        int v2 = index_map[f.v2];
        int v3 = index_map[f.v3];
        if (v1 != -1 && v2 != -1 && v3 != -1) {
            Face mapped{v1, v2, v3};
            if (!contains(rc.faces, mapped)) {
                rc.faces.push_back(mapped);
            }
        }
    }

    return kernel::to_c_mesh(rc);
}

Mesh boolean_intersect(const Mesh &a, const Mesh &b) {
    kernel::MeshCpp ac = kernel::to_cpp_mesh(a);
    kernel::MeshCpp bc = kernel::to_cpp_mesh(b);
    kernel::MeshCpp rc;
    std::vector<int> index_map_ac(ac.vertices.size(), -1);
    for (size_t i = 0; i < ac.vertices.size(); ++i) {
        if (contains(bc.vertices, ac.vertices[i])) {
            int idx = find_vertex(rc.vertices, ac.vertices[i]);
            if (idx == -1) {
                rc.vertices.push_back(ac.vertices[i]);
                idx = static_cast<int>(rc.vertices.size() - 1);
            }
            index_map_ac[i] = idx;
        }
    }

    for (const auto &f : ac.faces) {
        int a1 = index_map_ac[f.v1];
        int a2 = index_map_ac[f.v2];
        int a3 = index_map_ac[f.v3];
        if (a1 == -1 || a2 == -1 || a3 == -1) {
            continue;
        }
        int b1 = find_vertex(bc.vertices, ac.vertices[f.v1]);
        int b2 = find_vertex(bc.vertices, ac.vertices[f.v2]);
        int b3 = find_vertex(bc.vertices, ac.vertices[f.v3]);
        if (b1 == -1 || b2 == -1 || b3 == -1) {
            continue;
        }
        Face bf{b1, b2, b3};
        if (contains(bc.faces, bf)) {
            Face mapped{a1, a2, a3};
            if (!contains(rc.faces, mapped)) {
                rc.faces.push_back(mapped);
            }
        }
    }

    return kernel::to_c_mesh(rc);
}
