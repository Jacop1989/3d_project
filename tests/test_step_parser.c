#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../src/io/step_parser.h"
#include "../src/mesh.h"

int main(void) {
    const char *fname = "triangle.step";
    FILE *f = fopen(fname, "w");
    assert(f);
    fprintf(f, "ISO-10303-21;\n");
    fprintf(f, "HEADER;\nENDSEC;\nDATA;\n");
    fprintf(f, "#1 = CARTESIAN_POINT('', (0.,0.,0.));\n");
    fprintf(f, "#2 = CARTESIAN_POINT('', (1.,0.,0.));\n");
    fprintf(f, "#3 = CARTESIAN_POINT('', (0.,1.,0.));\n");
    fprintf(f, "#4 = TRIANGULAR_FACE('', (#1,#2,#3));\n");
    fprintf(f, "ENDSEC;\nEND-ISO-10303-21;\n");
    fclose(f);

    Mesh mesh;
    int ret = parse_step(fname, &mesh);
    assert(ret == 0);
    assert(mesh.vertex_count == 3);
    assert(mesh.face_count == 1);
    assert(mesh.vertices[0].x == 0.0f);
    assert(mesh.vertices[1].x == 1.0f);
    assert(mesh.faces[0].v1 == 0);
    assert(mesh.faces[0].v2 == 1);
    assert(mesh.faces[0].v3 == 2);

    free_mesh(&mesh);
    remove(fname);
    return 0;
}
