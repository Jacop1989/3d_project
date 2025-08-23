#include "mass_properties.h"

MassProperties compute_mass_properties(double volume, const Material& material) {
    MassProperties props;
    props.volume = volume;
    props.mass = volume * material.density;
    return props;
}
