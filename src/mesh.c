#include "mesh.h"
#include <stdlib.h>

void free_mesh(Mesh *mesh) {
    if (!mesh) return;
    free(mesh->vertices);
    free(mesh->faces);
    mesh->vertices = NULL;
    mesh->faces = NULL;
    mesh->vertex_count = 0;
    mesh->face_count = 0;
}
