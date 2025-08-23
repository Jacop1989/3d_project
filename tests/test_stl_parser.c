#include <assert.h>
#include <stdio.h>

#include "../src/io/stl_parser.h"
#include "../src/kernel/mesh.h"

int main(void) {
    const char *fname = "test.stl";
    FILE *f = fopen(fname, "w");
    assert(f);
    fprintf(f, "solid test\n");
    fprintf(f, "facet normal 0 0 1\n");
    fprintf(f, "outer loop\n");
    fprintf(f, "vertex 0 0 0\n");
    fprintf(f, "vertex 1 0 0\n");
    fprintf(f, "vertex 0 1 0\n");
    fprintf(f, "endloop\n");
    fprintf(f, "endfacet\n");
    fprintf(f, "endsolid\n");
    fclose(f);

    Mesh mesh;
    int ret = parse_stl(fname, &mesh);
    assert(ret == 0);
    assert(mesh.vertex_count == 3);
    assert(mesh.face_count == 1);
    assert(mesh.faces[0].v1 == 0);
    assert(mesh.faces[0].v2 == 1);
    assert(mesh.faces[0].v3 == 2);
    assert(mesh.vertices[1].x == 1.0f);

    free_mesh(&mesh);
    remove(fname);
    return 0;
}
