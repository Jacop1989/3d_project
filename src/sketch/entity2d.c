#include "entity2d.h"

Point2D point2d(double x, double y) {
    Point2D p = {x, y};
    return p;
}

Line2D line2d(Point2D p1, Point2D p2) {
    Line2D l = {p1, p2};
    return l;
}

Circle2D circle2d(Point2D c, double r) {
    Circle2D circ = {c, r};
    return circ;
}
