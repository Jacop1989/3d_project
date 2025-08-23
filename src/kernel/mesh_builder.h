#pragma once


#include <vector>
#include "vector3.h"

namespace kernel {

// Basic sketch representation as a list of vertices
struct Sketch {
    std::vector<Vector3> vertices;
};

// Triangle face referencing three vertex indices
struct Face {
    size_t v1;
    size_t v2;
    size_t v3;
};

// Simple mesh container holding vertices and faces
struct Mesh {
    std::vector<Vector3> vertices;
    std::vector<Face> faces;
};

// Build a very small mesh from sketch data
Mesh buildMeshFromSketch(const Sketch& sketch);

} // namespace kernel

