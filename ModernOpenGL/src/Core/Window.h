#ifndef CORE_WINDOW_H_
#define CORE_WINDOW_H_

#include <glm/vec2.hpp>

struct GLFWwindow;

class Window {
public:
    Window();
    ~Window();

    inline GLFWwindow* data() {
        return m_DataPtr;
    }

    inline glm::vec2& getMouseOffset() {
        return m_MouseOffset;
    }

    inline const glm::vec2& getMouseOffset() const {
        return m_MouseOffset;
    }

    constexpr bool isCursorDisabled() const {
        return m_IsCursorDisabled;
    }

    void onUpdate(float dt);

    bool shouldClose();
    void swapBuffer();

private:
    GLFWwindow* m_DataPtr;
    glm::vec2 m_MouseOffset;
    bool m_IsCursorDisabled;
};

#endif // !CORE_WINDOW_H_