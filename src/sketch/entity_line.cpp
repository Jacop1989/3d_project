#include "entity_line.h"

EntityLine::EntityLine(Point2D a, Point2D b) : p1(a), p2(b) {}

std::array<double*,4> EntityLine::parameters() {
    return {&p1.x, &p1.y, &p2.x, &p2.y};
}
