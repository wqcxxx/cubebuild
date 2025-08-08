#pragma once

#include <PerlinNoise.h>
#include <Chunk.h>
#include <Texture.h>

#include <memory>

class Generator 
{
    public:
        Generator(unsigned int seed);

        void generate_terrain(Chunk& chunk, const Texture& texture);
        void generate_terrain(std::unique_ptr<Chunk> chunk, const Texture& texture);
        void generate_terrain(Chunk* chunk, const Texture& texture);

    private:
        PerlinNoise m_noise;
};


