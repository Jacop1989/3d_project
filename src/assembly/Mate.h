#pragma once
#include <memory>
#include "Component.h"

class Mate {
public:
    Mate(std::shared_ptr<Component> a, std::shared_ptr<Component> b);
    virtual ~Mate() = default;
    std::shared_ptr<Component> first() const;
    std::shared_ptr<Component> second() const;
    virtual const char* type() const = 0;
protected:
    std::shared_ptr<Component> a_;
    std::shared_ptr<Component> b_;
};

