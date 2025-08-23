#pragma once

#include <vector>

namespace kernel {

// Basic sketch representation as a list of vertex coordinates
struct Sketch {
    std::vector<double> points; // x,y,z triples stored sequentially
};

// Triangle face referencing three vertex indices
struct Face {
    double v1;
    double v2;
    double v3;
};

// Simple mesh container
struct Mesh {
    std::vector<Face> faces;
};

// Build a very small mesh from sketch data
Mesh buildMeshFromSketch(const Sketch& sketch);

} // namespace kernel

