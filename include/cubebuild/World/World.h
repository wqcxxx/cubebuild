//#pragma once

// #include <Shader.h>
// #include <Chunk.h>
// #include <Generator.h>
// #include <Camera.h>

// #include <glm/glm.hpp>

// #include <utility>
// #include <memory>
// #include <vector>
// #include <unordered_map>

// class World 
// {
//     private:
//         using chunk_coordinates = std::pair<int, int>;
        
//         std::unordered_map<chunk_coordinates, std::unique_ptr<Chunk>> chunks;
//         std::vector<std::unique_ptr<Chunk>> dirty_chunks;

//         unsigned int m_seed;
//         Generator m_generator = Generator(m_seed);      

//         static size_t coord_to_hash(int x, int z);

//         int m_render_distance = 2;

//     public:
//         World(unsigned int seed);
//         ~World();
//         World(World&&) = default;  
//         World(const World&) = delete;

//         void update();
//         void update_dirty_chunks();
//         void setup_chunk(Chunk* chunk);
//         void load_chunk(int x, int y);
//         void render(Shader& shader);
//         void set_to_dirty_chunks(std::unique_ptr<Chunk> chunk);

//         void set_render_distance(int render_distance);
//         int get_render_distance();
// };