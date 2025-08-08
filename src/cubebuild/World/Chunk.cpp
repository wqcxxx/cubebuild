#include "Chunk.h"

Chunk::Chunk(int x, int z) : x(x), z(z)
{
    initialize_blocks();
}

Chunk::~Chunk() {}

void Chunk::initialize_blocks()
{
    blocks.resize(CHUNK_SIZE_X);

    for (auto& y_layer : blocks)
    {
        y_layer.resize(CHUNK_SIZE_Y);
        
        for (auto& z_layer : y_layer)
        {
            z_layer.resize(CHUNK_SIZE_Z);
        }
    }
}

void Chunk::render(Shader& shader) 
{
    for (int x = 0; x < CHUNK_SIZE_X; ++x)
    {
        for (int y = 0; y < CHUNK_SIZE_Y; ++y)
        {
            for (int z = 0; z < CHUNK_SIZE_Z; ++z)
            {
                if (blocks[x][y][z] && blocks[x][y][z]->is_active())
                {
                    blocks[x][y][z]->set_position(glm::vec3(this->x + x, y, this->z + z));
                    blocks[x][y][z]->draw(shader);
                }
            }
        }
    }
}

//getters

int Chunk::get_x() 
{ 
    return this->x; 
}

int Chunk::get_z() 
{ 
    return this->z; 
}

glm::vec2 Chunk::get_coords() 
{
    return glm::vec2(x, z);
}

Block* Chunk::get_block(int x, int y, int z) const
{
    if (x < 0 || x >= CHUNK_SIZE_X ||
        y < 0 || y >= CHUNK_SIZE_Y ||
        z < 0 || z >= CHUNK_SIZE_Z) 
        {
            return nullptr;
        }
    return blocks[x][y][z].get();
}

bool Chunk::has_flag(State flag) const
{
    return m_flags & flag;
}

//setters

void Chunk::set_block(int x, int y, int z, const Texture& texture, BlockType type, bool active)
{
    if (x < 0 || x >= CHUNK_SIZE_X ||
        y < 0 || y >= CHUNK_SIZE_Y ||
        z < 0 || z >= CHUNK_SIZE_Z) 
    {
        return;
    }
    
    if (!blocks[x][y][z])
    {
        blocks[x][y][z] = std::make_unique<Block>(texture, glm::vec3(x, y, z), type);
    }
    
    blocks[x][y][z]->set_active(active);
}

void Chunk::set_flag(State flag, bool value)
{
    if (value) m_flags |= flag;
    else m_flags &= ~flag;
}

void Chunk::mark_as_dirty()
{
    this->set_flag(State::needs_rebuild, true);
}
