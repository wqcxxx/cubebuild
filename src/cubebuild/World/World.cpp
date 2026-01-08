// #include "World.h"

// World::World(unsigned int seed) : m_seed(seed) {}

// World::~World() {}

// void World::setup_chunk(Chunk* chunk, const Texture& texture)
// {
//     if (!chunk->has_flag(Chunk::is_generated))
//     {
//         m_generator.generate_terrain(chunk, texture);
//         chunk->set_flag(Chunk::is_generated, true);
//     }
// }

// size_t World::coord_to_hash(int x, int z)
// {
//     return ((size_t)x << 32 | (size_t)z); 
// }

// void World::load_chunk(int x, int z, const Texture& texture)
// {
//     auto chunk = std::make_unique<Chunk>(x, z);
//     this->setup_chunk(chunk.get(), texture);
//     chunks[{x, z}] = std::move(chunk);
// }

// void World::render(Shader& shader, const Texture& texture)
// {
//     //glm::vec3 player_position = camera.get_position();

//     for (int x = 0; x < m_render_distance + 1; ++x)
//     {
//         for (int z = 0; z < m_render_distance + 1; ++z)
//         {
//             const auto coordinates = std::make_pair(x * Chunk::CHUNK_SIZE_X, z * Chunk::CHUNK_SIZE_Z);
//             auto it = chunks.find(coordinates);

//             if (it == chunks.end())
//             {
//                 //load_chunk(coordinates.first(), coordinates.second());
//             }
//             this->load_chunk(x*Chunk::CHUNK_SIZE_X, z*Chunk::CHUNK_SIZE_Z);
//             chunks[{x, z}]->render(shader);
//         }
//     }
// }

// void World::set_to_dirty_chunks(std::unique_ptr<Chunk> chunk)
// {
//     if (chunk->has_flag(Chunk::needs_rebuild)) 
//     {
//         //this->dirty_chunks.push_back(chunk);
//     }
// }

// void World::update_dirty_chunks()
// {
//     for (auto& chunk : dirty_chunks)
//     {
//         //rebuild
//     }
//     dirty_chunks.clear();
// }