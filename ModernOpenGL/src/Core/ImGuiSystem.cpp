#include "Core/ImGuiSystem.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Core/Log.h"

namespace ImGuiSystem {

bool init(GLFWwindow* window) {
    if (!IMGUI_CHECKVERSION()) {
        ERRORLOG("Failed to initialize Dear ImGui!\n");
        return false;
    }
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        ERRORLOG("Failed to initialize imgui_impl_glfw backend!\n");
        return false;
    }
    if (!ImGui_ImplOpenGL3_Init("#version 460")) {
        ERRORLOG("Failed to initialize imgui_impl_opengl3 backend!\n");
    }

    INFOLOG("Dear ImGui version - %s\n\n", IMGUI_VERSION);

    return true;
}

void newFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void render() {
    {
        ImGui::Begin("Dear ImGui Debugger");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void exit() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

} // namespace ImGuiSystem