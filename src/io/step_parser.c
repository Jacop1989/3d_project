#include "step_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Simple STEP parser
 * -------------------
 * The project originally contained only a stub here that was expected to be
 * replaced by an Open Cascade based implementation.  For the purposes of the
 * exercises and unit tests we provide a very small parser that understands a
 * tiny subset of STEP files:
 *
 *   - `CARTESIAN_POINT` entities describing vertices
 *   - `TRIANGULAR_FACE` entities referencing the vertex ids
 *
 * A minimal valid file therefore looks like:
 *
 *   ISO-10303-21;
 *   HEADER;
 *   ENDSEC;
 *   DATA;
 *   #1 = CARTESIAN_POINT('', (0.,0.,0.));
 *   #2 = CARTESIAN_POINT('', (1.,0.,0.));
 *   #3 = CARTESIAN_POINT('', (0.,1.,0.));
 *   #4 = TRIANGULAR_FACE('', (#1,#2,#3));
 *   ENDSEC;
 *   END-ISO-10303-21;
 *
 * Only the pieces relevant for testing are implemented and the parser is far
 * from a complete STEP implementation, but it demonstrates error handling and
 * conversion into the Mesh structure.
 */

typedef struct {
    int id;         /* STEP entity id (e.g. #1) */
    size_t index;   /* Index into the vertex array */
} IdMap;

static int lookup_index(const IdMap *map, size_t count, int id) {
    for (size_t i = 0; i < count; ++i) {
        if (map[i].id == id) {
            return (int)map[i].index;
        }
    }
    return -1;
}

int parse_step(const char *filename, Mesh *mesh) {
    if (!filename || !mesh) {
        return -1;
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return -1;
    }

    mesh->vertices = NULL;
    mesh->vertex_count = 0;
    mesh->faces = NULL;
    mesh->face_count = 0;

    Vertex *verts = NULL;
    size_t v_count = 0, v_cap = 0;
    Face *faces = NULL;
    size_t f_count = 0, f_cap = 0;
    IdMap *map = NULL;
    size_t map_count = 0, map_cap = 0;

    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        int id;
        if (sscanf(line, "#%d", &id) != 1) {
            continue; /* Ignore lines without an id */
        }

        if (strstr(line, "CARTESIAN_POINT")) {
            char *coords = strstr(line, "CARTESIAN_POINT");
            if (!coords) {
                continue;
            }
            coords = strchr(coords, '('); /* Skip to first '(' */
            if (!coords) {
                continue;
            }
            coords = strchr(coords + 1, '('); /* Coordinates are in the second pair of () */
            if (!coords) {
                continue;
            }

            float x, y, z;
            if (sscanf(coords + 1, "%f,%f,%f", &x, &y, &z) != 3) {
                goto fail;
            }

            if (v_count == v_cap) {
                size_t new_cap = v_cap ? v_cap * 2 : 8;
                Vertex *tmp = (Vertex *)realloc(verts, new_cap * sizeof(Vertex));
                if (!tmp) {
                    goto fail;
                }
                verts = tmp;
                v_cap = new_cap;
            }
            verts[v_count].x = x;
            verts[v_count].y = y;
            verts[v_count].z = z;

            if (map_count == map_cap) {
                size_t new_cap = map_cap ? map_cap * 2 : 8;
                IdMap *tmp = (IdMap *)realloc(map, new_cap * sizeof(IdMap));
                if (!tmp) {
                    goto fail;
                }
                map = tmp;
                map_cap = new_cap;
            }
            map[map_count].id = id;
            map[map_count].index = v_count;
            map_count++;
            v_count++;
        } else if (strstr(line, "TRIANGULAR_FACE")) {
            char *p = strstr(line, "TRIANGULAR_FACE");
            if (!p) {
                continue;
            }
            p = strchr(p, '(');
            if (!p) {
                continue;
            }
            p = strchr(p + 1, '(');
            if (!p) {
                continue;
            }
            int id1, id2, id3;
            if (sscanf(p + 1, "#%d,#%d,#%d", &id1, &id2, &id3) != 3) {
                goto fail;
            }
            int idx1 = lookup_index(map, map_count, id1);
            int idx2 = lookup_index(map, map_count, id2);
            int idx3 = lookup_index(map, map_count, id3);
            if (idx1 < 0 || idx2 < 0 || idx3 < 0) {
                goto fail;
            }

            if (f_count == f_cap) {
                size_t new_cap = f_cap ? f_cap * 2 : 8;
                Face *tmp = (Face *)realloc(faces, new_cap * sizeof(Face));
                if (!tmp) {
                    goto fail;
                }
                faces = tmp;
                f_cap = new_cap;
            }
            faces[f_count].v1 = idx1;
            faces[f_count].v2 = idx2;
            faces[f_count].v3 = idx3;
            f_count++;
        }
    }

    fclose(fp);
    free(map);

    mesh->vertices = verts;
    mesh->vertex_count = v_count;
    mesh->faces = faces;
    mesh->face_count = f_count;
    return 0;

fail:
    fclose(fp);
    free(map);
    free(verts);
    free(faces);
    mesh->vertices = NULL;
    mesh->faces = NULL;
    mesh->vertex_count = 0;
    mesh->face_count = 0;
    return -1;
}
