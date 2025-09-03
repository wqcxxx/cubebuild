#include "Generator.h"

#include <BlockType.h>
#include <algorithm>

Generator::Generator(unsigned int seed) : m_noise(seed) {}

void Generator::generate_terrain(Chunk& chunk, const Texture& texture)
{
    int chunk_x = chunk.get_x();
    int chunk_z = chunk.get_z();
    float scale = 0.17f;

    for (int x = 0; x < Chunk::CHUNK_SIZE_X; ++x) 
    {
        for (int z = 0; z < Chunk::CHUNK_SIZE_Z; ++z)
        {
            float w_x = (chunk_x + x) * scale;
            float w_z = (chunk_z + z) * scale;

            float noise_value = m_noise.noise2D(w_x, w_z);
            int height = 32 + (int)(noise_value);

            height = std::clamp(height, 0, Chunk::CHUNK_SIZE_Y - 1);

            for (int y = 0; y < Chunk::CHUNK_SIZE_Y; ++y) 
            {    
                BlockType type = BlockType::AIR_BLOCK;
                
                if (y <= height) 
                {
                    if(y == height) type = BlockType::GRASS_BLOCK;
                    else if(y > height - 4) type = BlockType::DIRT_BLOCK;
                    else type = BlockType::STONE_BLOCK;
                }
                
                chunk.set_block(x, y, z, texture, type, (type != BlockType::AIR_BLOCK));
            }
        }
    }
    chunk.set_flag(Chunk::is_generated, true);
}

void Generator::generate_terrain(std::unique_ptr<Chunk> chunk, const Texture& texture)
{
    int chunk_x = chunk->get_x();
    int chunk_z = chunk->get_z();
    float scale = 0.17f;

    for (int x = 0; x < Chunk::CHUNK_SIZE_X; ++x) 
    {
        for (int z = 0; z < Chunk::CHUNK_SIZE_Z; ++z)
        {
            float w_x = (chunk_x + x) * scale;
            float w_z = (chunk_z + z) * scale;

            float noise_value = m_noise.noise2D(w_x, w_z);
            int height = 32 + (int)(noise_value);

            height = std::clamp(height, 0, Chunk::CHUNK_SIZE_Y - 1);

            for (int y = 0; y < Chunk::CHUNK_SIZE_Y; ++y) 
            {    
                BlockType type = BlockType::AIR_BLOCK;
                
                if (y <= height) 
                {
                    if(y == height) type = BlockType::GRASS_BLOCK;
                    else if(y > height - 4) type = BlockType::DIRT_BLOCK;
                    else type = BlockType::STONE_BLOCK;
                }
                
                chunk->set_block(x, y, z, texture, type, (type != BlockType::AIR_BLOCK));
            }
        }
    }
    chunk->set_flag(Chunk::is_generated, true);
}

void Generator::generate_terrain(Chunk* chunk, const Texture& texture)
{
    int chunk_x = chunk->get_x();
    int chunk_z = chunk->get_z();
    float scale = 0.17f;

    for (int x = 0; x < Chunk::CHUNK_SIZE_X; ++x) 
    {
        for (int z = 0; z < Chunk::CHUNK_SIZE_Z; ++z)
        {
            float w_x = (chunk_x + x) * scale;
            float w_z = (chunk_z + z) * scale;

            float noise_value = m_noise.noise2D(w_x, w_z);
            int height = 32 + (int)(noise_value);

            height = std::clamp(height, 0, Chunk::CHUNK_SIZE_Y - 1);

            for (int y = 0; y < Chunk::CHUNK_SIZE_Y; ++y) 
            {    
                BlockType type = BlockType::AIR_BLOCK;
                
                if (y <= height) 
                {
                    if(y == height) type = BlockType::GRASS_BLOCK;
                    else if(y > height - 4) type = BlockType::DIRT_BLOCK;
                    else type = BlockType::STONE_BLOCK;
                }
                
                chunk->set_block(x, y, z, texture, type, (type != BlockType::AIR_BLOCK));
            }
        }
    }
    chunk->set_flag(Chunk::is_generated, true);
}

