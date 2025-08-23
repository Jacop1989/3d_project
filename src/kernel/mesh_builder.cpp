#include "mesh_builder.h"

namespace kernel {

Mesh buildMeshFromSketch(const Sketch& sketch) {
    Mesh mesh;
    // copy vertices into the mesh
    mesh.vertices = sketch.vertices;
    // For every three vertices in the sketch create one triangular face
    for (size_t i = 0; i + 2 < sketch.vertices.size(); i += 3) {
        Face f{i, i + 1, i + 2};
        mesh.faces.push_back(f);
    }
    return mesh;
}

} // namespace kernel

