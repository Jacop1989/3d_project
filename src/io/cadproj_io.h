#ifndef CADPROJ_IO_H
#define CADPROJ_IO_H

#include "../kernel/mesh.h"

/* Simple internal CAD project format (.cadproj) for storing meshes and
 * placeholders for parametric and assembly data. */
int load_cadproj(const char *filename, Mesh *mesh);
int save_cadproj(const char *filename, const Mesh *mesh);

#endif /* CADPROJ_IO_H */
