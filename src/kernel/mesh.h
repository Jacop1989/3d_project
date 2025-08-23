#ifndef KERNEL_MESH_H
#define KERNEL_MESH_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Basic data structures for 3D meshes used across C and C++ code */
typedef struct {
    float x, y, z;
} Vertex;

typedef struct {
    int v1, v2, v3;
} Face;

typedef struct {
    Vertex *vertices;
    size_t vertex_count;
    Face *faces;
    size_t face_count;
} Mesh;

void free_mesh(Mesh *mesh);

#ifdef __cplusplus
} // extern "C"

#include <vector>
#include <cstdlib>
#include "vector3.h"

namespace kernel {

/*
 * Helper container using C++ vectors. This is useful for legacy C++ code
 * while the rest of the system exposes the plain C Mesh structure.
 */
struct MeshCpp {
    std::vector<Vector3> vertices;
    std::vector<Face> faces;
};

// Convert a C++ MeshCpp to the C compatible Mesh structure.
inline Mesh to_c_mesh(const MeshCpp &src) {
    Mesh mesh{};
    mesh.vertex_count = src.vertices.size();
    if (mesh.vertex_count) {
        mesh.vertices = static_cast<Vertex*>(std::malloc(mesh.vertex_count * sizeof(Vertex)));
        for (size_t i = 0; i < mesh.vertex_count; ++i) {
            mesh.vertices[i].x = static_cast<float>(src.vertices[i].x);
            mesh.vertices[i].y = static_cast<float>(src.vertices[i].y);
            mesh.vertices[i].z = static_cast<float>(src.vertices[i].z);
        }
    } else {
        mesh.vertices = nullptr;
    }

    mesh.face_count = src.faces.size();
    if (mesh.face_count) {
        mesh.faces = static_cast<Face*>(std::malloc(mesh.face_count * sizeof(Face)));
        for (size_t i = 0; i < mesh.face_count; ++i) {
            mesh.faces[i] = src.faces[i];
        }
    } else {
        mesh.faces = nullptr;
    }

    return mesh;
}

// Convert a C compatible Mesh to the C++ MeshCpp representation.
inline MeshCpp to_cpp_mesh(const Mesh &src) {
    MeshCpp result;
    result.vertices.reserve(src.vertex_count);
    for (size_t i = 0; i < src.vertex_count; ++i) {
        const Vertex &v = src.vertices[i];
        result.vertices.emplace_back(v.x, v.y, v.z);
    }
    result.faces.reserve(src.face_count);
    for (size_t i = 0; i < src.face_count; ++i) {
        result.faces.push_back(src.faces[i]);
    }
    return result;
}

} // namespace kernel

#endif // __cplusplus

#endif /* KERNEL_MESH_H */
