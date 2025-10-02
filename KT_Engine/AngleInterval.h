#pragma once
#include "PrimaryType_Category.h"
#include "Math.h"
#include <stdexcept>

template<typename type> requires is_floating_type_v<type> 
class AngleInterval
{
public:
	AngleInterval(const type& min, const type& max);
	AngleInterval();
	AngleInterval(const AngleInterval& other);

	AngleInterval(AngleInterval&& other) noexcept;
	~AngleInterval() = default;
	type GetMin() const;

	type GetMax() const;


	type Normalize(const type& radiant) const;

	AngleInterval& operator=(const AngleInterval& other);

	AngleInterval& operator=(AngleInterval&& other) noexcept;

	bool operator==(const AngleInterval& other) const;

	bool operator!=(const AngleInterval& other) const;

	bool IsInInterval(const type& radiant) const;

private:
	type m_min;
	type m_max;
};

template <typename type> requires is_floating_type_v<type>
AngleInterval<type>::AngleInterval(const type& min, const type& max): m_min(min), m_max(max)
{
	if (m_min >= m_max)
		throw std::out_of_range("max must be higher than min");
}

template <typename type> requires is_floating_type_v<type>
AngleInterval<type>::AngleInterval() : m_min(type{}),m_max(type{})
{
}

template <typename type> requires is_floating_type_v<type>
AngleInterval<type>::AngleInterval(const AngleInterval& other): m_min(other.m_min), m_max(other.m_max)
{
	if (m_min >= m_max)
		throw std::out_of_range("max must be higher than min");
}

template <typename type> requires is_floating_type_v<type>
AngleInterval<type>::AngleInterval(AngleInterval&& other) noexcept: m_min(other.m_min), m_max(other.m_max)
{
	if (m_min >= m_max)
		throw std::out_of_range("max must be higher than min");
}

template <typename type> requires is_floating_type_v<type>
type AngleInterval<type>::GetMin() const
{
	return m_min;
}

template <typename type> requires is_floating_type_v<type>
type AngleInterval<type>::GetMax() const
{
	return m_max;
}

template <typename type> requires is_floating_type_v<type>
type AngleInterval<type>::Normalize(const type& radiant) const
{
	type range = m_max - m_min;
	type value = radiant - m_min;

	value = std::fmod(value, range);
	if (value < 0) value += range;

	return value + m_min;

}

template <typename type> requires is_floating_type_v<type>
AngleInterval<type>& AngleInterval<type>::operator=(const AngleInterval& other)
{
	m_min = other.m_min;
	m_max = other.m_max;
	return *this;
}

template <typename type> requires is_floating_type_v<type>
AngleInterval<type>& AngleInterval<type>::operator=(AngleInterval&& other) noexcept
{
	m_min = other.m_min;
	other.m_min = type{};
	m_max = other.m_max;
	other.m_max = type{};
	return *this;
}

template <typename type> requires is_floating_type_v<type>
bool AngleInterval<type>::operator==(const AngleInterval& other) const
{
	
		return Math::IsSameValue(m_min, other.m_min, Math::EPSILON_V<type>) && Math::IsSameValue(m_max, other.m_max, Math::EPSILON_V<type>);
	
}

template <typename type> requires is_floating_type_v<type>
bool AngleInterval<type>::operator!=(const AngleInterval& other) const
{

		return !Math::IsSameValue(m_min, other.m_min, Math::EPSILON_V<type>) || !Math::IsSameValue(m_max, other.m_max, Math::EPSILON_V<type>);
	
}

template <typename type> requires is_floating_type_v<type>
bool AngleInterval<type>::IsInInterval(const type& radiant) const
{
	if (radiant < m_min || radiant > m_max)
		return false;
	return true;
}

template<typename type> requires is_floating_type_v<type>
class UnsignedInterval :public AngleInterval<type>
{
public:
	UnsignedInterval();
	~UnsignedInterval() = default;
};

template <typename type> requires is_floating_type_v<type>
UnsignedInterval<type>::UnsignedInterval():AngleInterval<type>(0, 2 * Math::PI_V<type>)
{}

template<typename type> requires is_floating_type_v<type>
class SignedInterval :public AngleInterval<type>
{
public:
	SignedInterval();
	~SignedInterval() = default;
};

template <typename type> requires is_floating_type_v<type>
SignedInterval<type>::SignedInterval():AngleInterval<type>(-Math::PI_V<type>, Math::PI_V<type>)
{}

template<typename type, type min, type max> requires is_floating_type_v<type> && (min < max) && (max - min <= 2 * Math::PI_V<type>)
	class StaticAngleInterval
{
public:
	static constexpr type value_min = min;
	static constexpr type value_max = max;
	static type GetMin();

	static type GetMax();

	static type Normalize(const type& radiant);

	static bool IsInInterval(const type& radiant);
};

template <typename type, type min, type max> requires is_floating_type_v<type> && (min < max) && (max - min <= 2 * Math
	::PI_V<type>)
type StaticAngleInterval<type, min, max>::GetMin()
{
	return min;
}

template <typename type, type min, type max> requires is_floating_type_v<type> && (min < max) && (max - min <= 2 * Math
	::PI_V<type>)
type StaticAngleInterval<type, min, max>::GetMax()
{
	return max;
}

template <typename type, type min, type max> requires is_floating_type_v<type> && (min < max) && (max - min <= 2 * Math
	::PI_V<type>)
type StaticAngleInterval<type, min, max>::Normalize(const type& radiant)
{
	type range = max - min;
	type value = radiant - min;

	value = std::fmod(value, range);
	if (value < 0) value += range;

	return value + min;

}

template <typename type, type min, type max> requires is_floating_type_v<type> && (min < max) && (max - min <= 2 * Math
	::PI_V<type>)
bool StaticAngleInterval<type, min, max>::IsInInterval(const type& radiant)
{
	if (radiant < min || radiant > max)
		return false;
	return true;
}

template<typename type> requires is_floating_type_v<type>
using StaticUnsignedInterval = StaticAngleInterval<type, 0, 2 * Math::PI_V<type>>;
template<typename type> requires is_floating_type_v<type>
using StaticSignedInterval = StaticAngleInterval<type, -Math::PI_V<type>, Math::PI_V<type>>;
