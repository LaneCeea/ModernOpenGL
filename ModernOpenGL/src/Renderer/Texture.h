#ifndef RENDERER_TEXTURE_H_
#define RENDERER_TEXTURE_H_

#include <cstdint>
#include <string_view>

class Texture {
public:
    Texture(std::string_view filepath);
    ~Texture();

    void bind(std::uint32_t slot = 0) const;
    void unbind() const;

private:
    std::uint32_t m_RendererID;
    int m_Width, m_Height, m_Bpp;
};

#endif // !RENDERER_TEXTURE_H_