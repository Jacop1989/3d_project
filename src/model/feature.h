#pragma once
#include <vector>
#include <functional>
#include "../kernel/mesh.h"
#include "../kernel/vector3.h"

namespace model {

// Base class for modeling features which can notify when parameters change
class Feature {
public:
    virtual ~Feature() = default;
    // Generate the underlying geometry for the feature
    virtual Mesh generate() const = 0;

    void setOnChanged(std::function<void()> cb) { onChanged_ = std::move(cb); }

protected:
    void notifyChanged() { if (onChanged_) onChanged_(); }

private:
    std::function<void()> onChanged_;
};

// Simple extrude feature using a sketch profile and distance
class ExtrudeFeature : public Feature {
public:
    ExtrudeFeature(const std::vector<Vector3>& sketch, double distance);
    Mesh generate() const override;
    void setDistance(double d);
private:
    std::vector<Vector3> m_sketch;
    double m_distance;
};

// Revolve feature using a sketch profile and angle in degrees
class RevolveFeature : public Feature {
public:
    RevolveFeature(const std::vector<Vector3>& sketch, double angle);
    Mesh generate() const override;
    void setAngle(double a);
private:
    std::vector<Vector3> m_sketch;
    double m_angle;
};

} // namespace model

