#include "Random.hpp"

#include <cassert>

int Random::get_random_in_range(const int & min, const int & max)
{
    std::random_device m_random_device;
    std::mt19937 m_generator{m_random_device()};
    std::uniform_int_distribution<> distribution(min, max - 1);
    return distribution(m_generator);
}
