#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

class Texture 
{
    public:
        Texture(const char* path, int tile_size);
        ~Texture();

        void bind(GLenum texture);
        std::vector<glm::vec2> calculate_uvs(int tile_x, int lile_y) const;
        std::vector<glm::vec2> get_uv(int tile_x, int tile_y) const;

    private:
        GLuint m_textureID;
        int m_tile_size;
        int m_width, m_height;

        void load_texture(const char* path);
};