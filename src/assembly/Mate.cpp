#include "Mate.h"

Mate::Mate(std::shared_ptr<Component> a, std::shared_ptr<Component> b)
    : a_(std::move(a)), b_(std::move(b)) {}

std::shared_ptr<Component> Mate::first() const { return a_; }
std::shared_ptr<Component> Mate::second() const { return b_; }

