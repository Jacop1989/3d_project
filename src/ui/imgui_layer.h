#pragma once
#include <GLFW/glfw3.h>

namespace ImGuiLayer {
void Init(GLFWwindow* window);
void Shutdown();
void Begin();
void End();
}
