#include "constraint_panel.h"
#include <imgui.h>

namespace ui {

void constraint_panel(Solver *solver) {
    if (ImGui::Begin("Constraints")) {
        if (ImGui::Button("Solve")) {
            solver_solve(solver);
        }
        ImGui::End();
    }
}

} // namespace ui
