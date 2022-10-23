#include "Scene/TextureCube.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace scene {

TextureCube::TextureCube()
    : m_Vao(0),
    m_Shader("res/shaders/Texture_VP.glsl", "res/shaders/Texture_FP.glsl"),
    m_Texture("res/textures/celst.png"),
    m_Camera(), m_CurrentTime(0.0f) {

    glGenVertexArrays(1, &m_Vao);
    glBindVertexArray(m_Vao);
    {
        constexpr size_t STRIDE_COUNT = 9;
        const std::array<float, STRIDE_COUNT * 4 * 6> verticies = {
        //  Positions      | Colors                | TexCoord
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 0
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 1
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 2
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 3
        //  Positions      | Colors                | TexCoord
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 4
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 5
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 6
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 7
        //  Positions      | Colors                | TexCoord
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 8
        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 9
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 10
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 11
        //  Positions      | Colors                | TexCoord
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 12
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 13
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 14
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 15
        //  Positions      | Colors                | TexCoord
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 16
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 17
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 18
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 19
        //  Positions      | Colors                | TexCoord
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 20
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 21
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 22
        -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 23
        };

        const std::array<std::uint32_t, 3 * 2 * 6> indicies = {
            0 , 1 , 2 , 2 , 3 , 0 ,
            4 , 5 , 6 , 6 , 7 , 4 ,
            8 , 9 , 10, 10, 11, 8 ,
            12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16,
            20, 21, 22, 22, 23, 20,
        };

        std::uint32_t Vbo = 0;
        glGenBuffers(1, &Vbo);
        glBindBuffer(GL_ARRAY_BUFFER, Vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticies.size(), verticies.data(), GL_STATIC_DRAW);

        std::uint32_t Ebo = 0;
        glGenBuffers(1, &Ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * indicies.size(), indicies.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE_COUNT * sizeof(float), (const void*)(0));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, STRIDE_COUNT * sizeof(float), (const void*)(3 * sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, STRIDE_COUNT * sizeof(float), (const void*)(7 * sizeof(float)));
    }
    glBindVertexArray(0);

    m_Texture.bind(0);
    m_Shader.bind();
    m_Shader.setUniform("u_Texture", 0);
    m_Shader.unbind();
}

TextureCube::~TextureCube() {
    glDeleteVertexArrays(1, &m_Vao);
}

void TextureCube::onUpdate(float dt) {
    m_CurrentTime += dt;
    m_Camera.onUpdate(dt);
}

void TextureCube::onRender() {
    m_Shader.bind();
    for (const auto& cube_position : m_CubePositions) {
        float value = 1.0f;
        m_Shader.setUniform("u_Color", value, value, value, value);

        glm::mat4 model = glm::translate(glm::identity<glm::mat4>(), cube_position) * glm::rotate(glm::identity<glm::mat4>(), glm::radians(50.0f) * m_CurrentTime, glm::vec3(0.5f, 1.0f, 0.0f));
        glm::mat4 view = m_Camera.getViewMatrix();
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
        glm::mat4 mvp = proj * view * model;
        m_Shader.setUniform("u_Mvp", mvp);
        glBindVertexArray(m_Vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
    m_Shader.unbind();
}

void TextureCube::onImGuiRender() {
}

} // namespace scene