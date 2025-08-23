#include "mesh_builder.h"

namespace kernel {

Mesh buildMeshFromSketch(const Sketch& sketch) {
    Mesh mesh;
    // For every three vertices in the sketch create one triangular face
    for (size_t i = 0; i + 2 < sketch.points.size(); i += 3) {
        Face f{sketch.points[i], sketch.points[i + 1], sketch.points[i + 2]};
        mesh.faces.push_back(f);
    }
    return mesh;
}

} // namespace kernel

