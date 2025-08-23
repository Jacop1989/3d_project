#ifndef KERNEL_MASS_PROPERTIES_H
#define KERNEL_MASS_PROPERTIES_H

#include "../model/material.h"

struct MassProperties {
    double volume{0.0};
    double mass{0.0};
};

MassProperties compute_mass_properties(double volume, const Material& material);

#endif // KERNEL_MASS_PROPERTIES_H
