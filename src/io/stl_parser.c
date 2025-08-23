#include "stl_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_stl(const char *filename, Mesh *mesh) {
    if (!filename || !mesh)
        return -1;
    FILE *file = fopen(filename, "r");
    if (!file)
        return -1;

    char line[256];
    size_t vcap = 0, fcap = 0;
    size_t facet_vertex_count = 0;
    mesh->vertices = NULL;
    mesh->faces = NULL;
    mesh->vertex_count = 0;
    mesh->face_count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "vertex", 6) == 0) {
            if (mesh->vertex_count == vcap) {
                vcap = vcap ? vcap * 2 : 64;
                Vertex *tmp = realloc(mesh->vertices, vcap * sizeof(Vertex));
                if (!tmp)
                    goto error;
                mesh->vertices = tmp;
            }
            Vertex *v = &mesh->vertices[mesh->vertex_count++];
            if (sscanf(line + 6, "%f %f %f", &v->x, &v->y, &v->z) != 3)
                goto error;
            facet_vertex_count++;
        } else if (strncmp(line, "endfacet", 8) == 0) {
            if (facet_vertex_count != 3)
                goto error;
            if (mesh->face_count == fcap) {
                fcap = fcap ? fcap * 2 : 64;
                Face *tmp = realloc(mesh->faces, fcap * sizeof(Face));
                if (!tmp)
                    goto error;
                mesh->faces = tmp;
            }
            Face *f = &mesh->faces[mesh->face_count++];
            size_t base = mesh->vertex_count;
            f->v1 = base - 3;
            f->v2 = base - 2;
            f->v3 = base - 1;
            facet_vertex_count = 0;
        }
    }

    fclose(file);
    return 0;

error:
    fclose(file);
    free_mesh(mesh);
    return -1;
}
