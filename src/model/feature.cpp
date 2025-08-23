#include "feature.h"
#include "../kernel/mesh.h"
#include <cmath>

using kernel::MeshCpp;

namespace model {

ExtrudeFeature::ExtrudeFeature(const std::vector<Vector3>& sketch, double distance)
    : m_sketch(sketch), m_distance(distance) {}

void ExtrudeFeature::setDistance(double d) {
    m_distance = d;
    notifyChanged();
}

Mesh ExtrudeFeature::generate() const {
    MeshCpp mesh;
    size_t n = m_sketch.size();
    if (n < 3) {
        return kernel::to_c_mesh(mesh);
    }
    // bottom vertices
    for (const auto &p : m_sketch) {
        mesh.vertices.emplace_back(p.x, p.y, p.z);
    }
    // top vertices
    for (const auto &p : m_sketch) {
        mesh.vertices.emplace_back(p.x, p.y, p.z + m_distance);
    }
    // bottom and top faces (fan)
    for (size_t i = 1; i + 1 < n; ++i) {
        mesh.faces.push_back(Face{0, static_cast<int>(i + 1), static_cast<int>(i)});
        mesh.faces.push_back(Face{static_cast<int>(n), static_cast<int>(n + i), static_cast<int>(n + i + 1)});
    }
    // side faces
    for (size_t i = 0; i < n; ++i) {
        size_t next = (i + 1) % n;
        int b1 = static_cast<int>(i);
        int b2 = static_cast<int>(next);
        int t1 = static_cast<int>(i + n);
        int t2 = static_cast<int>(next + n);
        mesh.faces.push_back(Face{b1, b2, t1});
        mesh.faces.push_back(Face{b2, t2, t1});
    }
    return kernel::to_c_mesh(mesh);
}

RevolveFeature::RevolveFeature(const std::vector<Vector3>& sketch, double angle)
    : m_sketch(sketch), m_angle(angle) {}

void RevolveFeature::setAngle(double a) {
    m_angle = a;
    notifyChanged();
}

Mesh RevolveFeature::generate() const {
    MeshCpp mesh;
    size_t n = m_sketch.size();
    if (n < 2) {
        return kernel::to_c_mesh(mesh);
    }
    bool closed = std::abs(m_angle - 360.0) < 1e-6;
    int segments = closed ? 16 : std::max(3, static_cast<int>(std::ceil(m_angle / 15.0)));
    double angle_rad = m_angle * M_PI / 180.0;
    double step = closed ? 2 * M_PI / segments : angle_rad / segments;
    int ring_count = closed ? segments : segments + 1;
    for (int s = 0; s < ring_count; ++s) {
        double theta = step * s;
        double ct = std::cos(theta);
        double st = std::sin(theta);
        for (const auto &p : m_sketch) {
            double x = p.x * ct - p.y * st;
            double y = p.x * st + p.y * ct;
            mesh.vertices.emplace_back(x, y, p.z);
        }
    }
    for (int s = 0; s < segments; ++s) {
        int ring0 = s * n;
        int ring1 = closed ? ((s + 1) % segments) * n : (s + 1) * n;
        for (size_t i = 0; i + 1 < n; ++i) {
            int v00 = ring0 + i;
            int v01 = ring0 + i + 1;
            int v10 = ring1 + i;
            int v11 = ring1 + i + 1;
            mesh.faces.push_back(Face{v00, v01, v10});
            mesh.faces.push_back(Face{v01, v11, v10});
        }
    }
    return kernel::to_c_mesh(mesh);
}

} // namespace model

