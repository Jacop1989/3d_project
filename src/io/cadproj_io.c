#include "cadproj_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int save_cadproj(const char *filename, const Mesh *mesh) {
    if (!filename || !mesh) return -1;
    FILE *file = fopen(filename, "w");
    if (!file) return -1;

    fprintf(file, "CADPROJ 1.0\n");
    fprintf(file, "vertices %zu\n", mesh->vertex_count);
    for (size_t i = 0; i < mesh->vertex_count; ++i) {
        const Vertex *v = &mesh->vertices[i];
        fprintf(file, "%f %f %f\n", v->x, v->y, v->z);
    }

    fprintf(file, "faces %zu\n", mesh->face_count);
    for (size_t i = 0; i < mesh->face_count; ++i) {
        const Face *f = &mesh->faces[i];
        fprintf(file, "%d %d %d\n", f->v1, f->v2, f->v3);
    }

    fprintf(file, "# parametric and assembly data would follow\n");
    fclose(file);
    return 0;
}

int load_cadproj(const char *filename, Mesh *mesh) {
    if (!filename || !mesh) return -1;
    FILE *file = fopen(filename, "r");
    if (!file) return -1;

    char header[32];
    if (!fgets(header, sizeof(header), file) || strncmp(header, "CADPROJ", 7) != 0)
        goto error;

    size_t vcount = 0, fcount = 0, vcap = 0, fcap = 0;
    mesh->vertices = NULL;
    mesh->faces = NULL;
    mesh->vertex_count = 0;
    mesh->face_count = 0;

    char keyword[32];
    while (fscanf(file, "%31s", keyword) == 1) {
        if (strcmp(keyword, "vertices") == 0) {
            if (fscanf(file, "%zu", &vcount) != 1) goto error;
            vcap = vcount;
            mesh->vertices = malloc(vcap * sizeof(Vertex));
            if (!mesh->vertices) goto error;
            for (size_t i = 0; i < vcount; ++i) {
                Vertex *v = &mesh->vertices[i];
                if (fscanf(file, "%f %f %f", &v->x, &v->y, &v->z) != 3) goto error;
            }
            mesh->vertex_count = vcount;
        } else if (strcmp(keyword, "faces") == 0) {
            if (fscanf(file, "%zu", &fcount) != 1) goto error;
            fcap = fcount;
            mesh->faces = malloc(fcap * sizeof(Face));
            if (!mesh->faces) goto error;
            for (size_t i = 0; i < fcount; ++i) {
                Face *f = &mesh->faces[i];
                if (fscanf(file, "%d %d %d", &f->v1, &f->v2, &f->v3) != 3) goto error;
            }
            mesh->face_count = fcount;
        } else if (keyword[0] == '#') {
            fgets(header, sizeof(header), file); // skip comment
        } else {
            // Unrecognized section
            break;
        }
    }

    fclose(file);
    return 0;

error:
    fclose(file);
    free_mesh(mesh);
    return -1;
}
