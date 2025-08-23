#pragma once

#include "feature.h"

namespace model {

// Apply a fillet of given radius to a feature's sharp edges
void applyFillet(Feature& feature, double radius);

// Apply a chamfer of given distance to a feature's sharp edges
void applyChamfer(Feature& feature, double distance);

} // namespace model

