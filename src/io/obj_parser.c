#include "obj_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_obj(const char *filename, Mesh *mesh) {
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
        if (line[0] == 'v' && line[1] == ' ') {
            if (mesh->vertex_count == vcap) {
                vcap = vcap ? vcap * 2 : 64;
                mesh->vertices = realloc(mesh->vertices, vcap * sizeof(Vertex));
                if (!mesh->vertices) goto error;
            }
            Vertex *v = &mesh->vertices[mesh->vertex_count++];
            if (sscanf(line + 2, "%f %f %f", &v->x, &v->y, &v->z) != 3)
                goto error;
        } else if (line[0] == 'f' && line[1] == ' ') {
            if (mesh->face_count == fcap) {
                fcap = fcap ? fcap * 2 : 64;
                mesh->faces = realloc(mesh->faces, fcap * sizeof(Face));
                if (!mesh->faces) goto error;
            }
            Face *f = &mesh->faces[mesh->face_count++];
            if (sscanf(line + 2, "%d %d %d", &f->v1, &f->v2, &f->v3) != 3)
                goto error;
        }
    }

    fclose(file);
    return 0;

error:
    fclose(file);
    free_mesh(mesh);
    return -1;
}
