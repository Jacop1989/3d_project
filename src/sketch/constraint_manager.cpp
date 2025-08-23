#include "constraint_manager.h"
#include <cmath>

void ConstraintManager::addParameter(double* param) {
    params.push_back(param);
}

void ConstraintManager::addConstraint(const std::function<double()>& c) {
    constraints.push_back(c);
}

void ConstraintManager::solve(int iterations, double lr) {
    const double eps = 1e-6;
    for (int it = 0; it < iterations; ++it) {
        // Compute gradients
        std::vector<double> grads(params.size(), 0.0);
        for (size_t i = 0; i < params.size(); ++i) {
            double orig = *params[i];
            *params[i] = orig + eps;
            double err1 = 0.0;
            for (auto &c : constraints) {
                double v = c();
                err1 += v * v;
            }
            *params[i] = orig - eps;
            double err2 = 0.0;
            for (auto &c : constraints) {
                double v = c();
                err2 += v * v;
            }
            grads[i] = (err1 - err2) / (2 * eps);
            *params[i] = orig; // reset
        }
        // Apply gradient step
        for (size_t i = 0; i < params.size(); ++i) {
            *params[i] -= lr * grads[i];
        }
    }
}
