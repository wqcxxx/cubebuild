#pragma once 

#include <BlockType.h>
#include <Shader.h>
#include <Block.h>
#include <Texture.h>

#include <glm/glm.hpp>

#include <memory>
#include <vector>

class Chunk 
{
    public:
        enum State 
        {
            is_generated  = 1 << 0,
            needs_rebuild = 1 << 1,
            needs_render  = 1 << 2
        }; 

        static const int CHUNK_SIZE_X = 16;
        static const int CHUNK_SIZE_Y = 64;
        static const int CHUNK_SIZE_Z = 16;

        Chunk(int x, int z);
        ~Chunk();
        
        void set_flag(State flag, bool value);
        bool has_flag(State flag) const;

        void render(Shader& shader);

        void set_block(int x, int y, int z, const Texture& texture, BlockType type, bool active);
        void mark_as_dirty();
        
        Block* get_block(int x, int y, int z) const;
        glm::vec2 get_coords();
        int get_x();
        int get_z();

    private:
        int x, z;
        uint8_t m_flags = 0;
        std::vector<std::vector<std::vector<std::unique_ptr<Block>>>> blocks;

        void initialize_blocks();
};