#pragma once
#include <vector>
#include <functional>
#include "entity_line.h"

class ConstraintManager {
public:
    void addParameter(double* param);
    void addConstraint(const std::function<double()>& c);

    // Convenience helpers for common sketch constraints
    void addCoincident(Point2D& a, Point2D& b);
    void addPerpendicular(EntityLine& l1, EntityLine& l2);
    void addEqualLength(EntityLine& l1, EntityLine& l2);

    // Solve the nonlinear least squares system using a simple
    // Levenberg–Marquardt style Gauss–Newton iteration.
    void solve(int iterations = 20, double damping = 1e-3);
private:
    std::vector<double*> params;
    std::vector<std::function<double()>> constraints;
};
