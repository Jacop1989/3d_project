#include "feature.h"
#include <iostream>

namespace model {

ExtrudeFeature::ExtrudeFeature(const std::vector<double>& sketch, double distance)
    : m_sketch(sketch), m_distance(distance) {}

void ExtrudeFeature::generate() {
    // Placeholder implementation that would create a B-Rep from the sketch
    std::cout << "Generating extruded feature of distance " << m_distance << std::endl;
}

RevolveFeature::RevolveFeature(const std::vector<double>& sketch, double angle)
    : m_sketch(sketch), m_angle(angle) {}

void RevolveFeature::generate() {
    // Placeholder implementation that would create a revolved B-Rep from the sketch
    std::cout << "Generating revolved feature of angle " << m_angle << std::endl;
}

} // namespace model

