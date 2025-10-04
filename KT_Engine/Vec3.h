#pragma once
#include "VectorND.h"

template<typename type>
class Vec3 : public VectorND<type,3>
{
public:
	using value_type = type;
	using pointer_type = type*;
	using const_pointer_type = const type*;
	using reference_type = type&;
	using const_reference_type = const type&;
	Vec3();
	Vec3(const type& x_, const type& y_, const type& z_);
	Vec3(const Vec3& other);
	Vec3(Vec3&& other) noexcept;
	~Vec3() = default;
	Vec3& operator=(const Vec3& other);
	Vec3& operator=(Vec3&& other) noexcept;
	type& x;
	type& y;
	type& z;
	Vec3 Cross(const Vec3& other) const;
};

template <typename type>
Vec3<type>::Vec3() :VectorND<type,3>(),x(this->m_data[0]),y(this->m_data[1]),z(this->m_data[2]) {}

template <typename type>
Vec3<type>::Vec3(const type& x_, const type& y_, const type& z_) : VectorND<type,3>(x_,y_,z_), x(this->m_data[0]), y(this->m_data[1]), z(this->m_data[2]) {}

template <typename type>
Vec3<type>::Vec3(const Vec3& other) : VectorND<type, 3>(other), x(this->m_data[0]), y(this->m_data[1]), z(this->m_data[2]) {}

template <typename type>
Vec3<type>::Vec3(Vec3&& other) noexcept: VectorND<type, 3>(std::move(other)), x(this->m_data[0]), y(this->m_data[1]), z(this->m_data[2]){}

template <typename type>
Vec3<type>& Vec3<type>::operator=(const Vec3& other)
{
	VectorND<type, 3>::operator=(other);
	return *this;
}

template <typename type>
Vec3<type>& Vec3<type>::operator=(Vec3&& other) noexcept
{
	VectorND<type, 3>::operator=(std::move(other));
	return *this;
}

template <typename type>
Vec3<type> Vec3<type>::Cross(const Vec3& other) const
{
	return Vec3{
	 y * other.z - z * other.y,
	 z * other.x - x * other.z,
	x * other.y - y * other.x };
}
