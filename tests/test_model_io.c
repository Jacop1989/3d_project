#include <assert.h>
#include <stdio.h>
#include <string.h>

#define UNIT_TEST
#include "../3d_model_io.c"

int main() {
    const char *input = "test_input.obj";
    FILE *f = fopen(input, "w");
    fprintf(f, "v 0 0 0\n");
    fprintf(f, "v 1 0 0\n");
    fprintf(f, "v 0 1 0\n");
    fprintf(f, "f 1 2 3\n");
    fclose(f);

    vertex_count = 0;
    face_count = 0;
    load_obj(input);

    assert(vertex_count == 3);
    assert(face_count == 1);

    const char *output = "test_output.obj";
    save_obj(output);

    FILE *out = fopen(output, "r");
    int lines = 0;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), out)) {
        lines++;
    }
    fclose(out);

    assert(lines == vertex_count + face_count);

    remove(input);
    remove(output);
    return 0;
}
