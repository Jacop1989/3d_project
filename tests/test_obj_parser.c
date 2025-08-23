#include <assert.h>
#include <stdio.h>

#include "../src/io/obj_parser.h"
#include "../src/kernel/mesh.h"

int main(void) {
    const char *fname = "test.obj";
    FILE *f = fopen(fname, "w");
    assert(f);
    fprintf(f, "v 0 0 0\n");
    fprintf(f, "v 1 0 0\n");
    fprintf(f, "v 0 1 0\n");
    fprintf(f, "f 1 2 3\n");
    fclose(f);

    Mesh mesh;
    int ret = parse_obj(fname, &mesh);
    assert(ret == 0);
    assert(mesh.vertex_count == 3);
    assert(mesh.face_count == 1);
    assert(mesh.vertices[1].x == 1.0f);
    assert(mesh.faces[0].v1 == 1);
    assert(mesh.faces[0].v2 == 2);
    assert(mesh.faces[0].v3 == 3);

    free_mesh(&mesh);
    remove(fname);
    return 0;
}
