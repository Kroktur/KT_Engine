#include "Random.h"

Random::Random(): m_gen((m_rd()))
{}

Random& UseRandom()
{
	static Random rd;
	return rd;

}
