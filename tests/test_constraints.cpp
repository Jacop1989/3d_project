#include <cassert>
#include <cmath>
#include "../src/sketch/sketch.h"

int main() {
    // Coincident constraint test
    {
        Sketch s;
        auto &l1 = s.addLine({0,0},{1,0});
        auto &l2 = s.addLine({0,1},{1,1});
        // fix l1 endpoints
        s.addConstraint([&]{ return l1.p1.x - 0.0; });
        s.addConstraint([&]{ return l1.p1.y - 0.0; });
        s.addConstraint([&]{ return l1.p2.x - 1.0; });
        s.addConstraint([&]{ return l1.p2.y - 0.0; });
        // fix l2 second endpoint
        s.addConstraint([&]{ return l2.p2.x - 1.0; });
        s.addConstraint([&]{ return l2.p2.y - 1.0; });
        s.addCoincident(l1.p2, l2.p1);
        s.solve(100);
        assert(std::fabs(l1.p2.x - l2.p1.x) < 1e-3);
        assert(std::fabs(l1.p2.y - l2.p1.y) < 1e-3);
    }

    // Equal length standalone
    {
        Sketch s;
        auto &l1 = s.addLine({0,0},{2,0});
        auto &l2 = s.addLine({0,0},{0,1});
        // fix l1
        s.addConstraint([&]{ return l1.p1.x - 0.0; });
        s.addConstraint([&]{ return l1.p1.y - 0.0; });
        s.addConstraint([&]{ return l1.p2.x - 2.0; });
        s.addConstraint([&]{ return l1.p2.y - 0.0; });
        // fix l2 start point
        s.addConstraint([&]{ return l2.p1.x - 0.0; });
        s.addConstraint([&]{ return l2.p1.y - 0.0; });
        s.addEqualLength(l1, l2);
        s.solve(100);
        double dx2 = l2.p2.x - l2.p1.x;
        double dy2 = l2.p2.y - l2.p1.y;
        double len2 = std::sqrt(dx2*dx2 + dy2*dy2);
        assert(std::fabs(len2 - 2.0) < 1e-3);
    }

    return 0;
}
