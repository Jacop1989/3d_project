#include <iostream>
#include <cmath>
#include "../sketch/sketch.h"

int main() {
    Sketch sketch;
    auto &line = sketch.addLine({0,0}, {5,5});
    auto &circle = sketch.addCircle({5,0}, 3);

    sketch.addConstraint([&line]() {
        double dx = line.p2.x - line.p1.x;
        double dy = line.p2.y - line.p1.y;
        double len = std::sqrt(dx*dx + dy*dy);
        return len - 10.0; // target length 10
    });

    sketch.addConstraint([&circle]() {
        return circle.radius - 5.0; // target radius 5
    });

    std::cout << "Before solve:\n";
    std::cout << " Line: (" << line.p1.x << "," << line.p1.y << ") -> (" << line.p2.x << "," << line.p2.y << ")\n";
    std::cout << " Circle radius: " << circle.radius << "\n";

    sketch.solve();

    std::cout << "After solve:\n";
    std::cout << " Line: (" << line.p1.x << "," << line.p1.y << ") -> (" << line.p2.x << "," << line.p2.y << ")\n";
    std::cout << " Circle radius: " << circle.radius << "\n";

    std::cout << "Enter new end point for line (x y): ";
    std::cin >> line.p2.x >> line.p2.y;
    sketch.solve();
    std::cout << "After edit:\n";
    std::cout << " Line: (" << line.p1.x << "," << line.p1.y << ") -> (" << line.p2.x << "," << line.p2.y << ")\n";
    std::cout << " Circle radius: " << circle.radius << "\n";
    return 0;
}
