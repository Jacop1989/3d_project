#include <cassert>
#include <memory>
#include <string>

#include "../src/assembly/Assembly.h"
#include "../src/assembly/mates/AxisMate.h"
#include "../src/assembly/mates/PlaneMate.h"

int main() {
    auto c1 = std::make_shared<Component>("A");
    auto c2 = std::make_shared<Component>("B");

    Assembly a;
    a.addComponent(c1);
    a.addComponent(c2);
    assert(a.components().size() == 2);
    assert(a.components()[0]->name() == "A");

    auto m1 = std::make_shared<AxisMate>(c1, c2);
    a.addMate(m1);
    auto m2 = std::make_shared<PlaneMate>(c2, c1);
    a.addMate(m2);
    assert(a.mates().size() == 2);
    assert(std::string(a.mates()[0]->type()) == "AxisMate");
    assert(a.mates()[0]->first()->name() == "A");
    assert(a.mates()[0]->second()->name() == "B");
    assert(std::string(a.mates()[1]->type()) == "PlaneMate");

    return 0;
}
