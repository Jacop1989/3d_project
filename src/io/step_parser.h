#ifndef STEP_PARSER_H
#define STEP_PARSER_H

#include "../mesh.h"

/* Placeholder for STEP parsing. The implementation is expected to use
 * an external library such as Open Cascade in the future. */
int parse_step(const char *filename, Mesh *mesh);

#endif /* STEP_PARSER_H */
