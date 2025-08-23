#pragma once
#include <array>

struct Point2D {
    double x;
    double y;
};

class EntityLine {
public:
    Point2D p1;
    Point2D p2;

    EntityLine(Point2D a = {0,0}, Point2D b = {0,0});
    // Return vector of pointers to parameters for solver
    std::array<double*,4> parameters();
};
