#pragma once
#include <vector>
#include <memory>
#include "Component.h"
#include "Mate.h"

class Assembly {
public:
    void addComponent(std::shared_ptr<Component> comp);
    void addMate(std::shared_ptr<Mate> mate);
    const std::vector<std::shared_ptr<Component>>& components() const;
    const std::vector<std::shared_ptr<Mate>>& mates() const;
private:
    std::vector<std::shared_ptr<Component>> components_;
    std::vector<std::shared_ptr<Mate>> mates_;
};

