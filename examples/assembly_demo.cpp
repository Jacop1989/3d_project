#include <iostream>
#include <memory>
#include "assembly/Assembly.h"
#include "assembly/mates/PlaneMate.h"
#include "assembly/mates/AxisMate.h"

int main() {
    auto compA = std::make_shared<Component>("A");
    auto compB = std::make_shared<Component>("B");

    Assembly assembly;
    assembly.addComponent(compA);
    assembly.addComponent(compB);

    auto planeMate = std::make_shared<PlaneMate>(compA, compB);
    auto axisMate = std::make_shared<AxisMate>(compA, compB);

    assembly.addMate(planeMate);
    assembly.addMate(axisMate);

    std::cout << "Assembly has " << assembly.components().size() << " components and "
              << assembly.mates().size() << " mates." << std::endl;
    for (const auto& m : assembly.mates()) {
        std::cout << " - " << m->type() << std::endl;
    }
    return 0;
}

