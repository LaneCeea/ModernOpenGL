#include "Core/Timer.h"

#include <glfw/glfw3.h>

float Timer::getTime() {
    return static_cast<float>(glfwGetTime());
}