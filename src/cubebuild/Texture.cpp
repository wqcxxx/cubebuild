#include "Texture.h"
#include <iostream>
#include <filesystem>

#include "stb_image.h"

Texture::Texture(const char* path, int tile_size)
{
    load_texture(path);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_textureID);
}

void Texture::load_texture(const char* path)
{
    int nr_channels;
    unsigned char *data = stbi_load(path, &m_width, &m_height, &nr_channels, 0);

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLenum format = nr_channels == 4 ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void Texture::bind(GLenum texture)
{
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

std::vector<glm::vec2> Texture::calculate_uvs(int tile_x, int tile_y) const
{
    float tile_width = 1.0f / m_tile_size;
    float tile_height = 1.0f / m_tile_size;

    float u = tile_x * tile_width;
    float v = tile_y * tile_height;

    return 
    {
        {u, v + tile_height},
        {u + tile_width, v + tile_height},
        {u + tile_width, v},
        {u, v}
    };
}

std::vector<glm::vec2> Texture::get_uv(int tile_x, int tile_y) const
{
    return calculate_uvs(tile_x, tile_y);
}
