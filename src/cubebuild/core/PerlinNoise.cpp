#include "PerlinNoise.h"

PerlinNoise::PerlinNoise(unsigned int seed)
{
    m_permutation_table.resize(256);
    std::iota(m_permutation_table.begin(), m_permutation_table.end(), 0);
    std::shuffle(m_permutation_table.begin(), m_permutation_table.end(), std::default_random_engine(seed));
    m_permutation_table.insert(m_permutation_table.end(), m_permutation_table.begin(), m_permutation_table.end());
}

float PerlinNoise::noise2D(float x, float y)
{
    int X = (int)std::floor(x) & 255;
    int Y = (int)std::floor(y) & 255;

    float xf = x - std::floor(x);
    float yf = y - std::floor(y);

    float u = fade(xf);
    float v = fade(yf);

    int A = m_permutation_table[X] + Y;
    int B = m_permutation_table[X+1] + Y;

    float x1 = lerp(grad(m_permutation_table[A], x, y, 0), grad(m_permutation_table[B], x-1, y, 0), u);
    float x2 = lerp(grad(m_permutation_table[A+1], x, y-1, 0), grad(m_permutation_table[B+1], x-1, y-1, 0), u);

    return lerp(x1, x2, v);
}

float PerlinNoise::noise3D(float x, float y, float z)
{
    int X = (int)std::floor(x) & 255;
    int Y = (int)std::floor(y) & 255;
    int Z = (int)std::floor(z) & 255;

    float xf = x - std::floor(x);
    float yf = y - std::floor(y);
    float zf = z - std::floor(z);

    float u = fade(xf);
    float v = fade(yf);
    float w = fade(zf);

    int A = m_permutation_table[X] + Y;
    int B = m_permutation_table[X + 1] + Y;

    int AA = m_permutation_table[A] + Z;
    int AB = m_permutation_table[A + 1] + Z;
    
    int BA = m_permutation_table[B] + Z;
    int BB = m_permutation_table[B + 1] + Z;

    float p0 = grad(m_permutation_table[AA], xf, yf, zf);
    float p1 = grad(m_permutation_table[BA], xf - 1, yf, zf);
    float p2 = grad(m_permutation_table[AB], xf, yf - 1, zf);
    float p3 = grad(m_permutation_table[BB], xf - 1, yf - 1, zf);
    float p4 = grad(m_permutation_table[AA + 1], xf, yf, zf - 1);
    float p5 = grad(m_permutation_table[BA + 1], xf - 1, yf, zf - 1);
    float p6 = grad(m_permutation_table[AB + 1], xf, yf - 1, zf - 1);
    float p7 = grad(m_permutation_table[BB + 1], xf - 1, yf - 1, zf - 1);

    float q0 = lerp(p0, p1, u);
    float q1 = lerp(p2, p3, u);
    float q2 = lerp(p4, p5, u);
    float q3 = lerp(p6, p7, u);

    float r0 = lerp(q0, q1, v);
    float r1 = lerp(q2, q3, v);

    return lerp(r0, r1, w);
}
 
//does not work! needs to be fixed

// float PerlinNoise::octave_noise2D(int octaves, float persistence, float x, float y)
// {
//     float result = 0;
//     float amplitude = 0;

//     for (int i = 0; i < octaves; ++i)
//     {
//         result += (this->noise2D(x, y) * amplitude);
//         x *= 2;
//         y *= 2;
//         amplitude *= persistence;
//     }
//     return result;
// }

// float PerlinNoise::octave_noise3D(int octaves, float persistance, float x, float y, float z)
// {
//     float result = 0;
//     float amplitude = 1;
//     float max_value = 1;

//     for (int i = 0; i < octaves; ++i)
//     {
//         result += (this->noise3D(x, y, z) * amplitude);
//         x *= 2;
//         y *= 2;
//         z *= 3;
//         amplitude *= persistance;
//         max_value += amplitude;
//     }

//     return result / max_value;
// }

float PerlinNoise::lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

float PerlinNoise::fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise::grad(int hash, float x, float y, float z)
{
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}






