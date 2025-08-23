#include <cassert>
#include <cmath>
#include <memory>
#include "../src/model/feature.h"
#include "../src/model/history_tree.h"

static double computeVolume(const Mesh &mesh) {
    double vol = 0.0;
    for (size_t i = 0; i < mesh.face_count; ++i) {
        const Face &f = mesh.faces[i];
        const Vertex &a = mesh.vertices[f.v1];
        const Vertex &b = mesh.vertices[f.v2];
        const Vertex &c = mesh.vertices[f.v3];
        double v = a.x*(b.y*c.z - b.z*c.y) - a.y*(b.x*c.z - b.z*c.x) + a.z*(b.x*c.y - b.y*c.x);
        vol += v;
    }
    return std::fabs(vol) / 6.0;
}

int main() {
    using ::Vector3;
    using model::ExtrudeFeature;
    using model::RevolveFeature;
    using model::HistoryTree;

    // Test extrude feature
    std::vector<Vector3> square = { {0,0,0}, {1,0,0}, {1,1,0}, {0,1,0} };
    auto extrude = std::make_shared<ExtrudeFeature>(square, 1.0);
    HistoryTree tree1;
    tree1.addFeature(extrude);
    const Mesh &m1 = tree1.geometry();
    assert(m1.face_count == 12);
    double vol1 = computeVolume(m1);
    assert(std::fabs(vol1 - 1.0) < 1e-6);
    extrude->setDistance(2.0);
    const Mesh &m2 = tree1.geometry();
    double vol2 = computeVolume(m2);
    assert(std::fabs(vol2 - 2.0) < 1e-6);

    // Test revolve feature
    std::vector<Vector3> profile = { {0,0,0}, {1,0,0}, {1,0,1}, {0,0,1} };
    auto revolve = std::make_shared<RevolveFeature>(profile, 360.0);
    HistoryTree tree2;
    tree2.addFeature(revolve);
    const Mesh &mr = tree2.geometry();
    double volr = computeVolume(mr);
    assert(std::fabs(volr - M_PI) < 0.1);
    revolve->setAngle(180.0);
    double volr2 = computeVolume(tree2.geometry());
    assert(std::fabs(volr2 - (M_PI/2)) < 0.1);

    return 0;
}
