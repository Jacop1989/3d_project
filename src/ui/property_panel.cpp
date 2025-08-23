#include "property_panel.h"
#include <imgui.h>

bool edit_material(Material& material) {
    bool changed = false;
    changed |= ImGui::InputFloat("Density", &material.density);

    float color[3] = {material.color.r, material.color.g, material.color.b};
    if (ImGui::ColorEdit3("Color", color)) {
        material.color.r = color[0];
        material.color.g = color[1];
        material.color.b = color[2];
        changed = true;
    }

    return changed;
}
