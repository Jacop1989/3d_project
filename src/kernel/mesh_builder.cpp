#include "mesh_builder.h"

namespace kernel {

Mesh buildMeshFromSketch(const Sketch& sketch) {
    MeshCpp cpp;
    cpp.vertices = sketch.vertices;
    // For every three vertices in the sketch create one triangular face
    for (size_t i = 0; i + 2 < sketch.vertices.size(); i += 3) {
        Face f{static_cast<int>(i), static_cast<int>(i + 1), static_cast<int>(i + 2)};
        cpp.faces.push_back(f);
    }
    return to_c_mesh(cpp);
}

} // namespace kernel

