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
    a_cpp.vertices = {Vector3(0,0,0), Vector3(1,0,0)};
    kernel::MeshCpp b_cpp;
    b_cpp.vertices = {Vector3(1,0,0), Vector3(2,0,0)};
    Mesh a = kernel::to_c_mesh(a_cpp);
    Mesh b = kernel::to_c_mesh(b_cpp);

    Mesh u = boolean_union(a,b);
    assert(u.vertex_count == 3);

    Mesh s = boolean_subtract(a,b);
    assert(s.vertex_count == 1 && s.vertices[0].x == 0 && s.vertices[0].y == 0 && s.vertices[0].z == 0);

    Mesh i = boolean_intersect(a,b);
    assert(i.vertex_count == 1 && i.vertices[0].x == 1 && i.vertices[0].y == 0 && i.vertices[0].z == 0);

    free_mesh(&a);
    free_mesh(&b);
    free_mesh(&u);
    free_mesh(&s);
    free_mesh(&i);

    return 0;
}
