#ifndef SCENE_COLORCUBE_H_
#define SCENE_COLORCUBE_H_

#include <cstdint>
#include <string_view>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Scene/IScene.h"

namespace scene {

class ColorCube : public IScene {
public:
    ColorCube();
    ~ColorCube() override;

    void onUpdate(float dt) override;
    void onRender() override;
    void onImGuiRender() override;

    inline const std::string_view& getName() override {
        return NAME;
    }

public:
    static inline const std::string_view NAME = "Scene ColorCube";

private:
    std::uint32_t m_CubeVao, m_LightVao;
    glm::vec4 m_CubeColor, m_LightColor;
    glm::vec3 m_CubePos, m_LightPos;
    Shader m_CubeShader, m_LightShader;
    Camera m_Camera;
    float m_CurrentTime;
};

} // namespace scene

#endif // !SCENE_COLORCUBE_H_