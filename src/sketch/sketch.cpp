#include "sketch.h"

EntityLine& Sketch::addLine(Point2D a, Point2D b) {
    lines.emplace_back(a, b);
    auto params = lines.back().parameters();
    for (auto *p : params) cm.addParameter(p);
    return lines.back();
}

EntityCircle& Sketch::addCircle(Point2D c, double r) {
    circles.emplace_back(c, r);
    auto params = circles.back().parameters();
    for (auto *p : params) cm.addParameter(p);
    return circles.back();
}

void Sketch::addConstraint(const std::function<double()>& c) {
    cm.addConstraint(c);
}

void Sketch::solve() {
    cm.solve();
}
