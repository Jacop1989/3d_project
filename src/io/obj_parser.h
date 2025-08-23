#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include "../mesh.h"

/* Parse a Wavefront OBJ file into a Mesh structure.
 * Returns 0 on success, -1 on failure.
 */
int parse_obj(const char *filename, Mesh *mesh);

#endif /* OBJ_PARSER_H */
