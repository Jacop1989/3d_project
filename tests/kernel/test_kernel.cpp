#include <cassert>
#include "../../src/kernel/vector3.h"
#include "../../src/kernel/matrix4.h"
#include "../../src/kernel/boolean.h"

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
    Mesh a{{Vector3(0,0,0), Vector3(1,0,0)}};
    Mesh b{{Vector3(1,0,0), Vector3(2,0,0)}};

    Mesh u = boolean_union(a,b);
    assert(u.vertices.size() == 3);

    Mesh s = boolean_subtract(a,b);
    assert(s.vertices.size() == 1 && s.vertices[0] == Vector3(0,0,0));

    Mesh i = boolean_intersect(a,b);
    assert(i.vertices.size() == 1 && i.vertices[0] == Vector3(1,0,0));

    return 0;
}
