#ifndef MESH_H
#define MESH_H

#include <stddef.h>

/* Basic data structures for 3D meshes used by parsers */
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

#endif /* MESH_H */
