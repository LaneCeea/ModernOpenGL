#include "Core/Window.h"

#include <glfw/glfw3.h>

#include "Core/Log.h"

static glm::vec2 s_MouseOffset = glm::vec2(0.0f, 0.0f);

static void _MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    static glm::vec2 prev_pos = glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));
    const glm::vec2 curr_pos = glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));
    s_MouseOffset = curr_pos - prev_pos;
    prev_pos = curr_pos;
}

static bool s_IsKeyEscapePressed = false;

static void _KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    s_IsKeyEscapePressed = ((key == GLFW_KEY_ESCAPE) && (action != GLFW_RELEASE));
}

Window::Window()
    : m_DataPtr(nullptr), m_MouseOffset(0.0f, 0.0f), m_IsCursorDisabled(false) {
    m_DataPtr = glfwCreateWindow(1470, 810, "Modern OpenGL", nullptr, nullptr);
    if (!m_DataPtr)
        ERRORLOG("Failed to create window!\n");
    glfwMakeContextCurrent(m_DataPtr);
    glfwSetCursorPosCallback(m_DataPtr, _MouseCallback);
    glfwSetKeyCallback(m_DataPtr, _KeyCallback);
    glfwSwapInterval(1);
}

Window::~Window() {
    glfwDestroyWindow(m_DataPtr);
}

void Window::onUpdate(float dt) {

    if (s_IsKeyEscapePressed) {
        if (m_IsCursorDisabled) {
            glfwSetInputMode(m_DataPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            m_IsCursorDisabled = false;
            //INFOLOG("Enabled!\n");
        } else {
            glfwSetInputMode(m_DataPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            m_IsCursorDisabled = true;
            //INFOLOG("Disabled!\n");
        }
    } else {
        m_MouseOffset = s_MouseOffset;
    }
    s_IsKeyEscapePressed = false;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(m_DataPtr);
}

void Window::swapBuffer() {
    glfwSwapBuffers(m_DataPtr);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}