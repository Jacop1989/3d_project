#include "entity_circle.h"

EntityCircle::EntityCircle(Point2D c, double r) : center(c), radius(r) {}

std::array<double*,3> EntityCircle::parameters() {
    return {&center.x, &center.y, &radius};
}
