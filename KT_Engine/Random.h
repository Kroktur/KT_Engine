#pragma once
#include <random>
#include "PrimaryType_Category.h"

class Random
{
public:
    friend Random& UseRandom();
    template<typename type> requires is_floating_type_v<type>
    type getRandomNumber(type min, type max)
    {
        std::uniform_real_distribution<type> dis(min, max);
        return  static_cast<type>(dis(m_gen));
    }
	template<typename type> requires is_integral_type_v<type>
	type getRandomNumber(type min, type max)
    {
        std::uniform_int_distribution<type> dis(min, max);
        return static_cast<type>(dis(m_gen));
    }
private:
    Random();
    std::random_device m_rd;
    std::mt19937 m_gen;
};

Random& UseRandom();
