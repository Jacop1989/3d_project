#include "step_parser.h"
#include <stdio.h>

int parse_step(const char *filename, Mesh *mesh) {
    (void)filename;
    (void)mesh;
    fprintf(stderr, "STEP parsing not implemented. Future work will integrate Open Cascade.\n");
    return -1;
}
