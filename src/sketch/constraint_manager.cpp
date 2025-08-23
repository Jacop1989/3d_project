#include "constraint_manager.h"
#include <cmath>
#include <algorithm>

void ConstraintManager::addParameter(double* param) {
    params.push_back(param);
}

void ConstraintManager::addConstraint(const std::function<double()>& c) {
    constraints.push_back(c);
}

// --- constraint helpers -------------------------------------------------

void ConstraintManager::addCoincident(Point2D& a, Point2D& b) {
    addConstraint([&]() { return a.x - b.x; });
    addConstraint([&]() { return a.y - b.y; });
}

void ConstraintManager::addPerpendicular(EntityLine& l1, EntityLine& l2) {
    addConstraint([&]() {
        double dx1 = l1.p2.x - l1.p1.x;
        double dy1 = l1.p2.y - l1.p1.y;
        double dx2 = l2.p2.x - l2.p1.x;
        double dy2 = l2.p2.y - l2.p1.y;
        return dx1 * dx2 + dy1 * dy2; // dot product should be zero
    });
}

void ConstraintManager::addEqualLength(EntityLine& l1, EntityLine& l2) {
    addConstraint([&]() {
        double dx1 = l1.p2.x - l1.p1.x;
        double dy1 = l1.p2.y - l1.p1.y;
        double dx2 = l2.p2.x - l2.p1.x;
        double dy2 = l2.p2.y - l2.p1.y;
        double len1 = std::sqrt(dx1 * dx1 + dy1 * dy1);
        double len2 = std::sqrt(dx2 * dx2 + dy2 * dy2);
        return len1 - len2;
    });
}

// --- solver --------------------------------------------------------------

static std::vector<double> solveLinearSystem(std::vector<double> A, std::vector<double> b, int n) {
    // Simple Gauss-Jordan elimination
    for (int i = 0; i < n; ++i) {
        // Pivot
        int pivot = i;
        for (int r = i + 1; r < n; ++r) {
            if (std::fabs(A[r*n + i]) > std::fabs(A[pivot*n + i]))
                pivot = r;
        }
        if (pivot != i) {
            for (int c = 0; c < n; ++c)
                std::swap(A[i*n + c], A[pivot*n + c]);
            std::swap(b[i], b[pivot]);
        }
        double diag = A[i*n + i];
        if (std::fabs(diag) < 1e-12)
            continue; // singular; skip
        for (int c = i; c < n; ++c)
            A[i*n + c] /= diag;
        b[i] /= diag;
        for (int r = 0; r < n; ++r) {
            if (r == i) continue;
            double factor = A[r*n + i];
            for (int c = i; c < n; ++c)
                A[r*n + c] -= factor * A[i*n + c];
            b[r] -= factor * b[i];
        }
    }
    return b; // contains solution
}

void ConstraintManager::solve(int iterations, double damping) {
    const double eps = 1e-6;
    const int n = static_cast<int>(params.size());
    const int m = static_cast<int>(constraints.size());
    for (int it = 0; it < iterations; ++it) {
        // Evaluate constraint residuals
        std::vector<double> f(m);
        for (int i = 0; i < m; ++i)
            f[i] = constraints[i]();

        // Build Jacobian (finite differences)
        std::vector<double> J(m * n, 0.0);
        for (int j = 0; j < n; ++j) {
            double orig = *params[j];
            *params[j] = orig + eps;
            for (int i = 0; i < m; ++i) {
                double fp = constraints[i]();
                J[i*n + j] = (fp - f[i]) / eps;
            }
            *params[j] = orig; // reset
        }

        // Form normal equations J^T J * dx = -J^T f
        std::vector<double> A(n*n, 0.0);
        std::vector<double> b(n, 0.0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                double Jij = J[i*n + j];
                b[j] += -Jij * f[i];
                for (int k = 0; k < n; ++k)
                    A[j*n + k] += Jij * J[i*n + k];
            }
        }
        for (int j = 0; j < n; ++j)
            A[j*n + j] += damping;

        std::vector<double> dx = solveLinearSystem(A, b, n);

        double maxStep = 0.0;
        for (int j = 0; j < n; ++j) {
            *params[j] += dx[j];
            maxStep = std::max(maxStep, std::fabs(dx[j]));
        }
        if (maxStep < 1e-8)
            break; // converged
    }
}
