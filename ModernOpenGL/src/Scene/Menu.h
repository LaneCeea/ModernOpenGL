#ifndef SCENE_MENU_H_
#define SCENE_MENU_H_

#include <functional>
#include <string_view>
#include <vector>

#include <imgui/imgui.h>

#include "Core/Log.h"
#include "Scene/IScene.h"

namespace scene {

class Menu : public IScene {
public:
    Menu(IScene*& CurrPtr) : m_CurrentScenePtr(CurrPtr), m_Scenes() {}

    ~Menu() override {}

    void onImGuiRender() override {
        ImGui::Begin(NAME.data());
        for (const auto& Option : m_Scenes) {
            if (ImGui::Button(Option.Name.data())) {
                m_CurrentScenePtr = Option.ConstructFunc();
                break;
            }
        }
        ImGui::End();
    }

    inline const std::string_view& getName() override {
        return NAME;
    }

    template <class NewScene>
    void registerScene() {
        INFOLOG("Registering Scene: %s\n", NewScene::NAME.data());
        m_Scenes.emplace_back(NewScene::NAME, []() { return new NewScene(); });
    }

public:
    static inline const std::string_view NAME = "Scene Menu";

private:
    struct MenuOption {
        std::string_view Name;
        std::function<IScene* ()> ConstructFunc;

        MenuOption(const std::string_view& name, std::function<IScene* ()> func)
            : Name(name), ConstructFunc(func) {}
    };

private:
    IScene*& m_CurrentScenePtr;
    std::vector<MenuOption> m_Scenes;
};

} // namespace scene

#endif // !SCENE_MENU_H_