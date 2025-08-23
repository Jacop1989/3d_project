#include "imgui_layer.h"
#include "property_panel.h"
#include "../model/material.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

int main() {
    if (!glfwInit())
        return -1;
    GLFWwindow* window = glfwCreateWindow(800, 600, "Material Panel Demo", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ImGuiLayer::Init(window);

    Material material;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGuiLayer::Begin();
        if (ImGui::Begin("Material")) {
            edit_material(material);
        }
        ImGui::End();

        glViewport(0, 0, 800, 600);
        glClearColor(material.color.r, material.color.g, material.color.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGuiLayer::End();
        glfwSwapBuffers(window);
    }

    ImGuiLayer::Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
