#pragma once
#include "VectorND.h"

template<typename type> requires is_floating_type_v<type> || is_integral_type_v<type>
class Vec2 :public VectorND<type,2>
{
public:
	using value_type = type;
	using pointer_type = type*;
	using const_pointer_type = const type*;
	using reference_type = type&;
	using const_reference_type = const type&;

	Vec2();
	Vec2(const type& x_, const type& y_);
	Vec2(const Vec2& other);
	~Vec2() = default;
	Vec2& operator=(const Vec2& other);
	int& x;
	int& y;
	Vec2 NormalVector();
};

template <typename type> requires is_floating_type_v<type> || is_integral_type_v<type>
Vec2<type>::Vec2() : VectorND<type,2>(), x(this->m_data[0]), y(this->m_data[1]) {}

template <typename type> requires is_floating_type_v<type> || is_integral_type_v<type>
Vec2<type>::Vec2(const type& x_, const type& y_): VectorND<type,2>(x_,y_),x(this->m_data[0]),y(this->m_data[1]) {}

template <typename type> requires is_floating_type_v<type> || is_integral_type_v<type>
Vec2<type>::Vec2(const Vec2& other) : VectorND<type,2>(other.x,other.y),x(this->m_data[0]), y(this->m_data[1]) {}

template <typename type> requires is_floating_type_v<type> || is_integral_type_v<type>
Vec2<type>& Vec2<type>::operator=(const Vec2& other)
{
	VectorND<type, 2>::operator=(other);
	return *this;
}

template <typename type> requires is_floating_type_v<type> || is_integral_type_v<type>
Vec2<type> Vec2<type>::NormalVector() { return Vec2(-y, x); }
