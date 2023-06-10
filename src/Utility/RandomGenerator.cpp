#include "RandomGenerator.h"

void RandomGenerator::SetSeed(uint32_t seed)
{
    if (seed > 0)
    {
        m_seed = seed;
    }
    else
    {
        m_seed = m_randDevice();
    }

    std::mt19937 gen(m_seed);
    m_randGenerator = gen;
}

uint32_t RandomGenerator::GenerateNumber(uint32_t from, uint32_t to)
{
    std::uniform_int_distribution<uint32_t> randDist(from, to);
    return randDist(m_randGenerator);
}