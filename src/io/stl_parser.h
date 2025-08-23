#ifndef STL_PARSER_H
#define STL_PARSER_H

#include "../kernel/mesh.h"

/* Parse an ASCII STL file into a Mesh structure.
 * Returns 0 on success, -1 on failure.
 */
int parse_stl(const char *filename, Mesh *mesh);

#endif /* STL_PARSER_H */
