#ifndef RENDERER_SHADER_H_
#define RENDERER_SHADER_H_

#include <cstdint>
#include <string_view>
#include <unordered_map>

#include <glm/glm.hpp>

enum class ShaderType {
    NONE = -1, VERTEX, FRAGMENT
};

class Shader {
public:
    Shader(std::string_view vsfilepath, std::string_view fsfilepath);
    ~Shader();

    void bind();
    void unbind();

    void setUniform(std::string_view name, float v0) const;
    void setUniform(std::string_view name, float v0, float v1) const;
    void setUniform(std::string_view name, float v0, float v1, float v2) const;
    void setUniform(std::string_view name, float v0, float v1, float v2, float v3) const;
    void setUniform(std::string_view name, const glm::vec2& vec2) const;
    void setUniform(std::string_view name, const glm::vec3& vec3) const;
    void setUniform(std::string_view name, const glm::vec4& vec4) const;
    void setUniform(std::string_view name, int v0) const;
    void setUniform(std::string_view name, int v0, int v1) const;
    void setUniform(std::string_view name, int v0, int v1, int v2) const;
    void setUniform(std::string_view name, int v0, int v1, int v2, int v3) const;
    void setUniform(std::string_view name, std::uint32_t v0) const;
    void setUniform(std::string_view name, std::uint32_t v0, std::uint32_t v1) const;
    void setUniform(std::string_view name, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2) const;
    void setUniform(std::string_view name, std::uint32_t v0, std::uint32_t v1, std::uint32_t v2, std::uint32_t v3) const;
    void setUniform(std::string_view name, const glm::mat4& mat) const;

private:
    std::uint32_t _CompileShader(ShaderType type);
    int _GetUniformLocation(const std::string_view& name) const;

private:
    std::uint32_t m_RendererID;
    std::string_view m_FilePath[2];
    mutable std::unordered_map<std::string_view, int> m_UniformLocationCache;
    bool m_IsBinded;
};

#endif // !RENDERER_SHADER_H_