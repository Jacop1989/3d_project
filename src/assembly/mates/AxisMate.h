#pragma once
#include "../Mate.h"

class AxisMate : public Mate {
public:
    using Mate::Mate;
    const char* type() const override { return "AxisMate"; }
};

