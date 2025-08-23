#pragma once
#include "../Mate.h"

class PlaneMate : public Mate {
public:
    using Mate::Mate;
    const char* type() const override { return "PlaneMate"; }
};

