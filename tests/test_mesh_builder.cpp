#include <cassert>
#include "../src/kernel/mesh_builder.h"
#include "../src/kernel/mesh.h"

int main() {
    kernel::Sketch sketch;
    sketch.vertices = {
        Vector3(0,0,0), Vector3(1,0,0), Vector3(0,1,0),
        Vector3(0,0,1), Vector3(1,1,0), Vector3(1,0,1)
    };

    Mesh mesh = kernel::buildMeshFromSketch(sketch);

    assert(mesh.vertex_count == 6);
    assert(mesh.face_count == 2);

    assert(mesh.faces[0].v1 == 0 && mesh.faces[0].v2 == 1 && mesh.faces[0].v3 == 2);
    assert(mesh.faces[1].v1 == 3 && mesh.faces[1].v2 == 4 && mesh.faces[1].v3 == 5);

    assert(mesh.vertices[1].x == 1 && mesh.vertices[1].y == 0 && mesh.vertices[1].z == 0);
    assert(mesh.vertices[4].x == 1 && mesh.vertices[4].y == 1 && mesh.vertices[4].z == 0);

    free_mesh(&mesh);
    return 0;
}
