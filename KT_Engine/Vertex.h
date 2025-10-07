#pragma once
#include "Vec2.h"
#include "Vec3.h"

class Vertex
{
private:
	Vec3<float> m_position;
	Vec3<float> m_normal;
	Vec3<float> m_binormal;
	Vec3<float> m_tangent;
	Vec2<float> m_texturepos;
};
