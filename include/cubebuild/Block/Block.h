#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Shader.h>
#include <BlockType.h>
#include <Texture.h>

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
};

class Block {

    public:
        Block(const Texture& texture, const glm::vec3& position, BlockType type, const glm::vec3& size  = glm::vec3(1.0f)); 
        ~Block();

        void draw(Shader &shader);
        void set_position(const glm::vec3 &position);
        void set_block_type(BlockType block_type);
        void set_active(bool active);

        void create_block_mesh(const Texture& texture);

        bool is_active();
        glm::vec3 get_coords();

    private:
        GLuint m_VAO, m_VBO;
        BlockType m_block_type;
        bool m_is_active;
        glm::vec3 m_position;
        glm::vec3 m_size;
        std::vector<Vertex> vertices;

        void setup_mesh();
};