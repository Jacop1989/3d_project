#pragma once
#include "entity_line.h" // for Point2D
#include <array>

class EntityCircle {
public:
    Point2D center;
    double radius;

    EntityCircle(Point2D c = {0,0}, double r = 0.0);
    std::array<double*,3> parameters();
};
