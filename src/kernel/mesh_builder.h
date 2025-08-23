#pragma once


#include <vector>
#include "vector3.h"
#include "mesh.h"

namespace kernel {

// Basic sketch representation as a list of vertices
struct Sketch {
    std::vector<Vector3> vertices;
};

// Build a very small mesh from sketch data
Mesh buildMeshFromSketch(const Sketch& sketch);

} // namespace kernel

