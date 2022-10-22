#ifndef SCENE_TEXTURECUBE_H_
#define SCENE_TEXTURECUBE_H_

#include <cstdint>
#include <array>
#include <string_view>

#include <glm/vec3.hpp>

#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Scene/IScene.h"

namespace scene {

class TextureCube : public IScene {
public:
    TextureCube();
    ~TextureCube() override;

    void onUpdate(float dt) override;
    void onRender() override;
    void onImGuiRender() override;

    inline const std::string_view& getName() override {
        return NAME;
    }

public:
    static inline const std::string_view NAME = "Scene TextureCube";

private:
    static inline const std::array<glm::vec3, 10> m_CubePositions = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };
    std::uint32_t m_Vao;
    Shader m_Shader;
    Texture m_Texture;
    Camera m_Camera;
    float m_CurrentTime;
};

} // namespace scene

#endif // !SCENE_TEXTURECUBE_H_