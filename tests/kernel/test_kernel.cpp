#include <cassert>
#include "../../src/kernel/vector3.h"
#include "../../src/kernel/matrix4.h"
#include "../../src/kernel/boolean.h"
#include "../../src/kernel/mesh.h"

int main() {
    // Vector3 tests
    Vector3 v1(1,2,3), v2(1,1,1);
    Vector3 sum = v1 + v2;
    assert(sum == Vector3(2,3,4));
    Vector3 cross = v1.cross(v2);
    assert(cross == Vector3(-1,2,-1));

    // Matrix4 tests
    Matrix4 m = Matrix4::identity();
    m.m[3] = 1; // translate x by 1
    Vector3 transformed = m.transformPoint(Vector3(1,0,0));
    assert(transformed == Vector3(2,0,0));

    // Boolean tests
    kernel::MeshCpp a_cpp;
    a_cpp.vertices = {Vector3(0,0,0), Vector3(1,0,0), Vector3(0,1,0)};
    a_cpp.faces = { {0,1,2} };
    kernel::MeshCpp b_cpp;
    b_cpp.vertices = {Vector3(1,0,0), Vector3(0,1,0), Vector3(0,0,1)};
    b_cpp.faces = { {0,1,2} };
    Mesh a = kernel::to_c_mesh(a_cpp);
    Mesh b = kernel::to_c_mesh(b_cpp);

    Mesh u = boolean_union(a,b);
    assert(u.vertex_count == 4);
    assert(u.face_count == 2);
    bool has012 = false, has123 = false;
    for (size_t fi = 0; fi < u.face_count; ++fi) {
        const Face &f = u.faces[fi];
        if (f.v1 == 0 && f.v2 == 1 && f.v3 == 2) has012 = true;
        if (f.v1 == 1 && f.v2 == 2 && f.v3 == 3) has123 = true;
    }
    assert(has012 && has123);

    Mesh s = boolean_subtract(a,b);
    assert(s.vertex_count == 1 && s.face_count == 0 &&
           s.vertices[0].x == 0 && s.vertices[0].y == 0 && s.vertices[0].z == 0);

    Mesh i = boolean_intersect(a,b);
    assert(i.vertex_count == 2 && i.face_count == 0);

    free_mesh(&a);
    free_mesh(&b);
    free_mesh(&u);
    free_mesh(&s);
    free_mesh(&i);

    return 0;
}
