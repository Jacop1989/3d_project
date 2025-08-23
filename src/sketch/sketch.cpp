
#include "sketch.h"

EntityLine& Sketch::addLine(Point2D a, Point2D b) {
    // std::list keeps previously inserted elements at stable addresses, so
    // parameter pointers stored in the ConstraintManager remain valid.
    lines.emplace_back(a, b);
    EntityLine &line = lines.back();
    auto params = line.parameters();
    for (auto *p : params) cm.addParameter(p);
    return line;
}

EntityCircle& Sketch::addCircle(Point2D c, double r) {
    circles.emplace_back(c, r);
    EntityCircle &circle = circles.back();
    auto params = circle.parameters();
    for (auto *p : params) cm.addParameter(p);
    return circle;
}

void Sketch::addConstraint(const std::function<double()>& c) {
    cm.addConstraint(c);
}

void Sketch::solve(int iterations) {
    cm.solve(iterations);
}

namespace sketch {
void placeholder() {}
} // namespace sketch

