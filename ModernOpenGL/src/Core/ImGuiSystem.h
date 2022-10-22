#ifndef CORE_IMGUISYSTEM_H_
#define CORE_IMGUISYSTEM_H_

struct GLFWwindow;

namespace ImGuiSystem {

bool init(GLFWwindow* window);

void newFrame();

void render();

void exit();

} // namespace ImGuiSystem

#endif // !CORE_IMGUISYSTEM_H_