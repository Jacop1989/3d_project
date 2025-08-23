#pragma once
#include <vector>

namespace model {

class Feature {
public:
    virtual ~Feature() = default;
    // Generate the underlying geometry for the feature
    virtual void generate() = 0;
};

// Simple extrude feature using a sketch profile and distance
class ExtrudeFeature : public Feature {
public:
    ExtrudeFeature(const std::vector<double>& sketch, double distance);
    void generate() override;
private:
    std::vector<double> m_sketch;
    double m_distance;
};

// Revolve feature using a sketch profile and angle in degrees
class RevolveFeature : public Feature {
public:
    RevolveFeature(const std::vector<double>& sketch, double angle);
    void generate() override;
private:
    std::vector<double> m_sketch;
    double m_angle;
};

} // namespace model

