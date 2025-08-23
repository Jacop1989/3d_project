#include "viewport.h"
#include "imgui_layer.h"
#include <glad/glad.h>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h> // for mouse wheel? not needed but include
#include <glm/glm.hpp> // optional
#include <glm/gtc/matrix_transform.hpp>

Viewport::Viewport(int width, int height, const char* title)
    : m_Window(nullptr), m_Width(width), m_Height(height) {
    if (!glfwInit())
        return;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_Window) {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_Window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ImGuiLayer::Init(m_Window);
}

Viewport::~Viewport() {
    ImGuiLayer::Shutdown();
    if (m_Window)
        glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Viewport::ProcessInput() {
    ImGuiIO& io = ImGui::GetIO();
    double x, y;

    if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !io.WantCaptureMouse) {
        if (!m_Rotating) {
            m_Rotating = true;
            glfwGetCursorPos(m_Window, &m_LastX, &m_LastY);
        } else {
            glfwGetCursorPos(m_Window, &x, &y);
            m_Yaw   += static_cast<float>(x - m_LastX) * 0.01f;
            m_Pitch += static_cast<float>(y - m_LastY) * 0.01f;
            m_LastX = x;
            m_LastY = y;
        }
    } else {
        m_Rotating = false;
    }

    if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS && !io.WantCaptureMouse) {
        if (!m_Panning) {
            m_Panning = true;
            glfwGetCursorPos(m_Window, &m_LastX, &m_LastY);
        } else {
            glfwGetCursorPos(m_Window, &x, &y);
            // use difference for panning (not stored here)
            m_LastX = x;
            m_LastY = y;
        }
    } else {
        m_Panning = false;
    }

    if (!io.WantCaptureMouse) {
        m_Distance -= io.MouseWheel * 0.5f;
        if (m_Distance < 1.0f)
            m_Distance = 1.0f;
    }
}

uint32_t Viewport::Pick(int x, int y) {
    uint32_t pixel = 0;
    glReadPixels(x, m_Height - y, 1, 1, GL_RED_INTEGER, GL_UNSIGNED_INT, &pixel);
    return pixel;
}

void Viewport::Run() {
    while (m_Window && !glfwWindowShouldClose(m_Window)) {
        glfwPollEvents();
        ProcessInput();

        glViewport(0, 0, m_Width, m_Height);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGuiLayer::Begin();
        if (ImGui::Begin("Viewport")) {
            ImGui::Text("Camera distance: %.2f", m_Distance);
            ImGui::Text("Yaw: %.2f Pitch: %.2f", m_Yaw, m_Pitch);
        }
        ImGui::End();
        ImGuiLayer::End();

        glfwSwapBuffers(m_Window);
    }
}
