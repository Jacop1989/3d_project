#include "property_panel.h"
#include <iostream>

void edit_material(Material& material) {
    std::cout << "Enter density: ";
    std::cin >> material.density;
    std::cout << "Enter color (r g b): ";
    std::cin >> material.color.r >> material.color.g >> material.color.b;
}
