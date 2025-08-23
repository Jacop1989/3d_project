# 3D Project

This repository experiments with simple 3D file parsing and rendering.

## I/O Library

New parsers for common mesh formats live in `src/io/`:

- `obj_parser.c` – loads Wavefront OBJ files.
- `stl_parser.c` – loads ASCII STL files.
- `cadproj_io.c` – reads and writes the experimental `.cadproj` format.
- `step_parser.c` – placeholder for future STEP support via external
  libraries such as Open Cascade.

The shared `Mesh` data structure is defined in `src/kernel/mesh.h`.

See [`docs/cadproj_format.md`](docs/cadproj_format.md) for details on the
`.cadproj` design.

