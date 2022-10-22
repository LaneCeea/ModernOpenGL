#include "Renderer/Texture.h"

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Core/Log.h"

Texture::Texture(std::string_view filepath)
    : m_RendererID(0), m_Width(0), m_Height(0), m_Bpp(0) {
    stbi_set_flip_vertically_on_load(true);

    std::uint8_t* LocalBuffer = stbi_load(filepath.data(), &m_Width, &m_Height, &m_Bpp, 4);
    if (!LocalBuffer) {
        ERRORLOG("Failed to load image from %s!", filepath.data());
        return;
    }

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D, 0,
        GL_RGBA8, m_Width, m_Height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(LocalBuffer);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_RendererID);
}

void Texture::bind(std::uint32_t slot) const {
    glActiveTexture(slot + GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
