#include "Renderer/Shader.h"

#include <malloc.h>

#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>

#include <glad/glad.h>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Log.h"

Shader::Shader(std::string_view vsfilepath, std::string_view fsfilepath) 
    : m_RendererID(0), m_FilePath{ vsfilepath, fsfilepath }, m_UniformLocationCache(), m_IsBinded(false) {
    std::uint32_t program = glCreateProgram();
    std::uint32_t vs = _CompileShader(ShaderType::VERTEX);
    std::uint32_t fs = _CompileShader(ShaderType::FRAGMENT);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    int success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        int length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* message = reinterpret_cast<char*>(_malloca(length));
        glGetProgramInfoLog(program, length, nullptr, message);
        ERRORLOG("Failed to link program - %s\n", message);
    }

    m_RendererID = program;
}

Shader::~Shader() {
    glDeleteProgram(m_RendererID);
}

void Shader::bind() {
    if (m_IsBinded) {
        WARNINGLOG("Attempt to bind a binded shader!\n");
        return;
    }
    glUseProgram(m_RendererID);
    m_IsBinded = true;
}

void Shader::unbind() {
    if (!m_IsBinded) {
        WARNINGLOG("Attempt to unbind a unbinded shader!\n");
        return;
    }
    glUseProgram(0);
    m_IsBinded = false;
}

void Shader::setUniform(std::string_view name, float v0) const {
    int location = _GetUniformLocation(name.data());
    glUniform1f(location, v0);
}

void Shader::setUniform(std::string_view name, float v0, float v1) const {
    int location = _GetUniformLocation(name.data());
    glUniform2f(location, v0, v1);
}

void Shader::setUniform(std::string_view name, float v0, float v1, float v2) const {
    int location = _GetUniformLocation(name.data());
    glUniform3f(location, v0, v1, v2);
}

void Shader::setUniform(std::string_view name, float v0, float v1, float v2, float v3) const {
    int location = _GetUniformLocation(name.data());
    glUniform4f(location, v0, v1, v2, v3);
}

void Shader::setUniform(std::string_view name, int v0) const {
    int location = _GetUniformLocation(name.data());
    glUniform1i(location, v0);
}

void Shader::setUniform(std::string_view name, int v0, int v1) const {
    int location = _GetUniformLocation(name.data());
    glUniform2i(location, v0, v1);
}

void Shader::setUniform(std::string_view name, int v0, int v1, int v2) const {
    int location = _GetUniformLocation(name.data());
    glUniform3i(location, v0, v1, v2);
}

void Shader::setUniform(std::string_view name, int v0, int v1, int v2, int v3) const {
    int location = _GetUniformLocation(name.data());
    glUniform4i(location, v0, v1, v2, v3);
}

void Shader::setUniform(std::string_view name, std::uint32_t v0) const {
    int location = _GetUniformLocation(name.data());
    glUniform1ui(location, v0);
}

void Shader::setUniform(std::string_view name, std::uint32_t v0, std::uint32_t v1) const {
    int location = _GetUniformLocation(name.data());
    glUniform2ui(location, v0, v1);
}

void Shader::setUniform(std::string_view name, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2) const {
    int location = _GetUniformLocation(name.data());
    glUniform3ui(location, v0, v1, v2);
}

void Shader::setUniform(std::string_view name, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2, std::uint32_t v3) const {
    int location = _GetUniformLocation(name.data());
    glUniform4ui(location, v0, v1, v2, v3);
}

void Shader::setUniform(std::string_view name, const glm::mat4& mat) const {
    int location = _GetUniformLocation(name.data());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

std::uint32_t Shader::_CompileShader(ShaderType type) {
    std::uint32_t shader = 0;
    switch (type) {
    case ShaderType::VERTEX:
        shader = glCreateShader(GL_VERTEX_SHADER);
        break;
    
    case ShaderType::FRAGMENT:
        shader = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    }

    std::ifstream file(m_FilePath[static_cast<size_t>(type)].data());
    std::ostringstream buffer;
    buffer << file.rdbuf();
    const std::string str = buffer.str();
    const char* source = str.data();

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        int length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* message = reinterpret_cast<char*>(_malloca(length));
        glGetShaderInfoLog(shader, length, nullptr, message);
        ERRORLOG("Failed to compile shader - %s\n", message);

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

int Shader::_GetUniformLocation(const std::string_view& name) const {
    auto it = m_UniformLocationCache.find(name);
    if (it != m_UniformLocationCache.end())
        return it->second;

    int location = glGetUniformLocation(m_RendererID, name.data());
    if (location == -1)
        WARNINGLOG("Warning: uniform '%s' does not exist!\n", name.data());

    m_UniformLocationCache.emplace(name, location);
    return location;
}
