#include "stl_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_stl(const char *filename, Mesh *mesh) {
    if (!filename || !mesh) return -1;
    FILE *file = fopen(filename, "r");
    if (!file) return -1;

    char line[256];
    size_t vcap = 0, fcap = 0;
    mesh->vertices = NULL;
    mesh->faces = NULL;
    mesh->vertex_count = 0;
    mesh->face_count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "vertex", 6) == 0) {
            if (mesh->vertex_count == vcap) {
                vcap = vcap ? vcap * 2 : 64;
                mesh->vertices = realloc(mesh->vertices, vcap * sizeof(Vertex));
                if (!mesh->vertices) goto error;
            }
            Vertex *v = &mesh->vertices[mesh->vertex_count++];
            if (sscanf(line + 6, "%f %f %f", &v->x, &v->y, &v->z) != 3)
                goto error;
        } else if (strncmp(line, "endfacet", 8) == 0) {
            if (mesh->face_count == fcap) {
                fcap = fcap ? fcap * 2 : 64;
                mesh->faces = realloc(mesh->faces, fcap * sizeof(Face));
                if (!mesh->faces) goto error;
            }
            Face *f = &mesh->faces[mesh->face_count++];
            size_t base = mesh->vertex_count;
            // Each facet adds 3 vertices sequentially
            f->v1 = base - 3;
            f->v2 = base - 2;
            f->v3 = base - 1;
        }
    }

    fclose(file);
    return 0;

error:
    fclose(file);
    free_mesh(mesh);
    return -1;
}
