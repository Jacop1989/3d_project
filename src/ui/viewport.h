#pragma once
#include <GLFW/glfw3.h>
#include <cstdint>

class Viewport {
public:
    Viewport(int width, int height, const char* title);
    ~Viewport();

    void Run();

private:
    void ProcessInput();
    uint32_t Pick(int x, int y);

    GLFWwindow* m_Window;
    int m_Width;
    int m_Height;

    float m_Distance = 5.0f;
    float m_Yaw = 0.0f;
    float m_Pitch = 0.0f;

    double m_LastX = 0.0;
    double m_LastY = 0.0;
    bool m_Rotating = false;
    bool m_Panning = false;
};
