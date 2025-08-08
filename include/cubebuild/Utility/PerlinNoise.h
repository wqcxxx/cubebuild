#pragma once

#include <vector>
#include <numeric>
#include <random>
#include <algorithm>

class PerlinNoise {
public:
    PerlinNoise(unsigned int seed = 0);

    float noise2D(float x, float y);
    float noise3D(float x, float y, float z);
    // float octave_noise2D(int octaves, float persistence, float x, float y);
    // float octave_noise3D(int octaves, float persistance, float x, float y, float z);

private:
    std::vector<int> m_permutation_table;

    float fade(float t);
    float lerp(float a, float b, float t);
    float grad(int hash, float x, float y, float z);

};