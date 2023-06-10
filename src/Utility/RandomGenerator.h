#pragma once
#include <random>

class RandomGenerator
{
public:
    RandomGenerator() = delete;
    ~RandomGenerator() = delete;
    RandomGenerator(const RandomGenerator& randomGenerator) = delete;
    RandomGenerator operator=(const RandomGenerator& randomGenerator) = delete;

    static void SetSeed(uint32_t seed = 0);

    static uint32_t GenerateNumber(uint32_t from, uint32_t to);

private:
    static inline std::random_device m_randDevice;
    static inline std::random_device::result_type m_seed;
    static inline std::mt19937 m_randGenerator;
};