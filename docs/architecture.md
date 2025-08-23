# Architecture

The project consists of several simple C modules:

- `3d_model_io.c` implements basic OBJ file loading and saving.
- `3d_model_viewer.c` provides a simple OpenGL viewer for OBJ models.
- `3d_points_and_line.c` demonstrates drawing points, lines, and axes with OpenGL.

Tests focus on the model I/O module. CI builds and executes these tests on each push.
