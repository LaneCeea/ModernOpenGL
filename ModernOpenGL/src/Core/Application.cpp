#include "Core/Application.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Core/GLSystem.h"
#include "Core/ImGuiSystem.h"
#include "Core/Timer.h"
#include "Scene/Menu.h"
#include "Scene/TextureCube.h"

Application::Application()
    : m_Window(nullptr) {
    GLSystem::initGLFW();
    m_Window = std::make_unique<Window>();
    GLSystem::initGLAD();
    ImGuiSystem::init(m_Window->data());
}

void Application::run() {
    scene::IScene* curr = nullptr;
    scene::Menu* menu = new scene::Menu(curr);
    curr = menu;
        
    menu->registerScene<scene::TextureCube>();
    
    m_LastFrameTime = Timer::getTime();
    while (!m_Window->shouldClose()) {
        float curr_frame = Timer::getTime();
        float dt = curr_frame - m_LastFrameTime;
        m_LastFrameTime = curr_frame;
            
        m_Window->onUpdate(dt);

        ImGuiSystem::newFrame();

        if (curr) {
            curr->onUpdate(dt);
            curr->onRender();
            if (curr != menu) {
                ImGui::Begin(curr->getName().data());
                if (ImGui::Button("Return to Menu")) {
                    delete curr;
                    curr = menu;
                }
                ImGui::End();
            }
            curr->onImGuiRender();
        }

        ImGuiSystem::render();
        m_Window->swapBuffer();
    }
    
}

Application::~Application() {
    ImGuiSystem::exit();
    m_Window.release();
    GLSystem::exit();
}
