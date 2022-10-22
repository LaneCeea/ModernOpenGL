#include "Core/Input.h"

#include <glfw/glfw3.h>

#include "Core/Application.h"

bool Input::isKeyPressed(const KeyCode key) {
	auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().data());
	auto state = glfwGetKey(window, static_cast<int32_t>(key));
	return state == GLFW_PRESS;
}

bool Input::isMouseButtonPressed(const MouseCode button) {
	auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().data());
	auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
	return state == GLFW_PRESS;
}

glm::vec2 Input::getMousePosition() {
	auto* window = static_cast<GLFWwindow*>(Application::get().getWindow().data());
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	return { (float)xpos, (float)ypos };
}

float Input::getMouseX() {
	return getMousePosition().x;
}

float Input::getMouseY() {
	return getMousePosition().y;
}