#include "Assembly.h"

void Assembly::addComponent(std::shared_ptr<Component> comp) {
    components_.push_back(std::move(comp));
}

void Assembly::addMate(std::shared_ptr<Mate> mate) {
    mates_.push_back(std::move(mate));
}

const std::vector<std::shared_ptr<Component>>& Assembly::components() const {
    return components_;
}

const std::vector<std::shared_ptr<Mate>>& Assembly::mates() const {
    return mates_;
}

