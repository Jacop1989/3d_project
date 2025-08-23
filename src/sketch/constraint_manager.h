#pragma once
#include <vector>
#include <functional>

class ConstraintManager {
public:
    void addParameter(double* param);
    void addConstraint(const std::function<double()>& c);
    void solve(int iterations = 100, double lr = 0.1);
private:
    std::vector<double*> params;
    std::vector<std::function<double()>> constraints;
};
