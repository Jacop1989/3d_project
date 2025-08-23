#include "feature_operations.h"
#include <iostream>

namespace model {

void applyFillet(Feature& feature, double radius) {
    // In a full implementation this would modify the feature's geometry
    std::cout << "Applying fillet with radius " << radius << std::endl;
    feature.generate();
}

void applyChamfer(Feature& feature, double distance) {
    // In a full implementation this would modify the feature's geometry
    std::cout << "Applying chamfer with distance " << distance << std::endl;
    feature.generate();
}

} // namespace model

