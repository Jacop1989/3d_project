#pragma once
#include <list>
#include <functional>
#include "entity_line.h"
#include "entity_circle.h"
#include "constraint_manager.h"

class Sketch {
public:
    EntityLine& addLine(Point2D a, Point2D b);
    EntityCircle& addCircle(Point2D c, double r);
    void addConstraint(const std::function<double()>& c);
    void addCoincident(Point2D& a, Point2D& b) { cm.addCoincident(a,b); }
    void addPerpendicular(EntityLine& l1, EntityLine& l2) { cm.addPerpendicular(l1,l2); }
    void addEqualLength(EntityLine& l1, EntityLine& l2) { cm.addEqualLength(l1,l2); }
    void solve(int iterations = 20);
    const std::list<EntityLine>& getLines() const { return lines; }
    const std::list<EntityCircle>& getCircles() const { return circles; }
private:
    // Use std::list to keep entity addresses stable so that parameter
    // pointers registered with the ConstraintManager remain valid after
    // inserting new elements.
    std::list<EntityLine> lines;
    std::list<EntityCircle> circles;
    ConstraintManager cm;
};
