#include "Scene/ColorCube.h"

#include <array>

#include <glad/glad.h>
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace scene {

ColorCube::ColorCube()
    : m_CubeVao(0), m_LightVao(0),
    m_CubeColor(1.0f, 0.5f, 0.3f, 1.0f), m_LightColor(1.0f, 1.0f, 1.0f, 1.0f),
    m_CubePos(0.0f, 0.0f, 0.0f), m_LightPos(1.2f, 1.0f, 2.0f),
    m_CubeShader("res/shaders/Color_VP.glsl", "res/shaders/Color_FP.glsl"),
    m_LightShader("res/shaders/Light_VP.glsl", "res/shaders/Light_FP.glsl"),
    m_Camera(), m_CurrentTime(0.0f) {

    constexpr size_t STRIDE_COUNT = 3;
    const std::array<float, STRIDE_COUNT * 4 * 6> verticies = {
        //  Positions      |
        -0.5f, -0.5f, -0.5f, // 0
         0.5f, -0.5f, -0.5f, // 1
         0.5f,  0.5f, -0.5f, // 2
        -0.5f,  0.5f, -0.5f, // 3
        //  Positions      |
        -0.5f, -0.5f,  0.5f, // 4
         0.5f, -0.5f,  0.5f, // 5
         0.5f,  0.5f,  0.5f, // 6
        -0.5f,  0.5f,  0.5f, // 7
        //  Positions      |
        -0.5f, -0.5f,  0.5f, // 8
        -0.5f,  0.5f,  0.5f, // 9
        -0.5f,  0.5f, -0.5f, // 10
        -0.5f, -0.5f, -0.5f, // 11
        //  Positions      |
         0.5f, -0.5f,  0.5f, // 12
         0.5f,  0.5f,  0.5f, // 13
         0.5f,  0.5f, -0.5f, // 14
         0.5f, -0.5f, -0.5f, // 15
        //  Positions      |
        -0.5f, -0.5f,  0.5f, // 16
         0.5f, -0.5f,  0.5f, // 17
         0.5f, -0.5f, -0.5f, // 18
        -0.5f, -0.5f, -0.5f, // 19
        //  Positions      |
        -0.5f,  0.5f,  0.5f, // 20
         0.5f,  0.5f,  0.5f, // 21
         0.5f,  0.5f, -0.5f, // 22
        -0.5f,  0.5f, -0.5f, // 23
    };

    const std::array<std::uint32_t, 3 * 2 * 6> indicies = {
        0 , 1 , 2 , 2 , 3 , 0 ,
        4 , 5 , 6 , 6 , 7 , 4 ,
        8 , 9 , 10, 10, 11, 8 ,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20,
    };

    // Cube VAO
    glGenVertexArrays(1, &m_CubeVao);
    glBindVertexArray(m_CubeVao);

    std::uint32_t Vbo = 0;
    glGenBuffers(1, &Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, Vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticies.size(), verticies.data(), GL_STATIC_DRAW);

    std::uint32_t Ebo = 0;
    glGenBuffers(1, &Ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * indicies.size(), indicies.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_COUNT * sizeof(float), (const void*)(0));
    glBindVertexArray(0);

    // Light VAO
    glGenVertexArrays(1, &m_LightVao);
    glBindVertexArray(m_LightVao);
    glBindBuffer(GL_ARRAY_BUFFER, Vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_COUNT * sizeof(float), (const void*)(0));
    glBindVertexArray(0);
}

ColorCube::~ColorCube() {
    glDeleteVertexArrays(1, &m_CubeVao);
    glDeleteVertexArrays(1, &m_LightVao);
}

void ColorCube::onUpdate(float dt) {
    m_CurrentTime += dt;
    m_Camera.onUpdate(dt);
}

void ColorCube::onRender() {
    const glm::mat4 view = m_Camera.getViewMatrix();
    const glm::mat4 proj = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
    const glm::mat4 projview = proj * view;

    m_CubeShader.bind();
    m_CubeShader.setUniform("u_ObjectColor", m_CubeColor);
    m_CubeShader.setUniform("u_LightColor", m_LightColor);
    const glm::mat4 cube_model = glm::translate(glm::identity<glm::mat4>(), m_CubePos);
    const glm::mat4 cube_mvp = projview * cube_model;
    m_CubeShader.setUniform("u_Mvp", cube_mvp);
    glBindVertexArray(m_CubeVao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    m_CubeShader.unbind();
    
    m_LightShader.bind();
    m_LightShader.setUniform("u_LightColor", m_LightColor);
    const glm::mat4 light_model = glm::scale(glm::translate(glm::identity<glm::mat4>(), m_LightPos), glm::vec3(0.2f));
    const glm::mat4 light_mvp = projview * light_model;
    m_LightShader.setUniform("u_Mvp", light_mvp);
    glBindVertexArray(m_LightVao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    m_LightShader.unbind();
    
}

void ColorCube::onImGuiRender() {
    ImGui::Begin(NAME.data());
    ImGui::SliderFloat4("Cube Color", glm::value_ptr(m_CubeColor), 0.0f, 1.0f);
    ImGui::SliderFloat4("Light Color", glm::value_ptr(m_LightColor), 0.0f, 1.0f);
    ImGui::End();
}

} // namespace scene