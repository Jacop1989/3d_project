#ifndef STEP_PARSER_H
#define STEP_PARSER_H

#include "../kernel/mesh.h"

/* Parse a minimal subset of STEP files and populate @mesh.
 *
 * The current implementation supports CARTESIAN_POINT entities describing
 * vertices and TRIANGULAR_FACE entities referencing those vertices.  The
 * function returns 0 on success and -1 on failure. */
int parse_step(const char *filename, Mesh *mesh);

#endif /* STEP_PARSER_H */
