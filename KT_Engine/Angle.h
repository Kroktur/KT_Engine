#pragma once
#include "AngleInterval.h"
template<typename type> requires is_floating_type_v<type>
class Angle;

template<typename type> requires is_floating_type_v<type>
Angle< type> Degree(const type& degree, AngleInterval<type>* interval);

template<typename type> requires is_floating_type_v<type>
Angle < type> Radiant(const type& radiant, AngleInterval<type>* interval);

template<typename type> requires is_floating_type_v<type>
class Angle
{
public:
	friend Angle Degree<type>(const type&, AngleInterval<type>*);
	friend Angle Radiant<type>(const type&, AngleInterval<type>*);
	using value_type = type;
	using pointer_type = type*;
	using const_pointer_type = const type*;
	using reference_type = type&;
	using const_reference_type = const type&;

	Angle(AngleInterval<type>* strategy = new UnsignedInterval<type>{}) :m_radiants(type{}), m_strategy(std::move(strategy)){}
	~Angle()
	{
		delete m_strategy;
		m_strategy = nullptr;
	}
	Angle(const Angle& other) :m_radiants(other.m_radiants),m_strategy(other.m_strategy) {}
	Angle(Angle&& other) noexcept : m_radiants(other.m_radiants), m_strategy(std::move(other.m_strategy))
	{
		other.m_radiants = type{};
		other.m_strategy = nullptr;
	}
	type AsRadians()
	{
		return m_strategy->Normalize(m_radiants);
	}

	type AsRadians() const
	{
		return m_strategy->Normalize(m_radiants);
	}
	type AsDegrees()
	{
		return m_strategy->Normalize(m_radiants) * static_cast<type>(180) / Math::PI_V<type>;
	}
	type AsDegrees() const
	{
		return m_strategy->Normalize(m_radiants) * static_cast<type>(180) / Math::PI_V<type>;
	}
	Angle& operator=(const Angle& other)
	{
		m_radiants = other.m_radiants;
		m_strategy = other.m_strategy;
		return *this;
	}
	Angle& operator=(Angle&& other) noexcept
	{
		m_radiants = other.m_radiants;
		other.m_radiants = type{};
		m_strategy = std::move(other.m_strategy);
		other.m_strategy = nullptr;
		return *this;
	}

	/*Angle operator+(const Angle& other) const
	{
		return Angle(m_radiants + other.m_radiants, new AngleInterval<type>(m_strategy->GetMin(),m_strategy->GetMax()));
	}

	Angle operator-(const Angle& other) const
	{
		return Angle(m_radiants - other.m_radiants, new AngleInterval<type>(m_strategy->GetMin(), m_strategy->GetMax()));
	}

	Angle& operator +=(const Angle& other);

	Angle& operator -=(const Angle& other);

	Angle operator*(const_reference_type factor) const;

	Angle operator/(const_reference_type divider) const;

	Angle& operator *=(const_reference_type factor);

	Angle& operator /=(const_reference_type divider);

	bool operator==(const Angle& other) const;

	bool operator!=(const Angle& other) const;

	AngleInterval<type> GetInterval() const;*/
private:
	Angle(const type& radiant,  AngleInterval<type>* interval) : m_radiants(radiant),m_strategy(interval){}
	type m_radiants;
	AngleInterval<type>* m_strategy;
};


template <typename type> requires is_floating_type_v<type>
Angle<type> Degree(const type& degree, AngleInterval<type>* interval)
{
	auto rad = degree * (Math::PI_V<type> / static_cast<type>(180));
	return Angle<type>(rad, interval);
}



template <typename type> requires is_floating_type_v<type>
Angle<type> Radiant(const type& radiant, AngleInterval<type>* interval)
{
	return Angle<type>(radiant, interval);
}
template<typename type, typename AngleInterval > requires is_floating_type_v<type>
class StaticAngle;

template<typename type, typename AngleInterval > requires is_floating_type_v<type>
StaticAngle< type, AngleInterval> Degree(const type&);

template<typename type, typename AngleInterval > requires is_floating_type_v<type>
StaticAngle < type, AngleInterval> Radiant(const type&);


template<typename type, typename AngleInterval > requires is_floating_type_v<type>
class StaticAngle
{
public:
	friend StaticAngle Degree<type,AngleInterval>(const type&);
	friend StaticAngle Radiant<type, AngleInterval>(const type&);
	using value_type = type;
	using pointer_type = type*;
	using const_pointer_type = const type*;
	using reference_type = type&;
	using const_reference_type = const type&;
	using Interval = StaticAngleInterval<type, AngleInterval::value_min, AngleInterval::value_max>;

	StaticAngle();
	~StaticAngle() = default;
	StaticAngle(const StaticAngle& other);
	StaticAngle(StaticAngle&& other) noexcept;
	type AsRadians();

	type AsRadians() const;
	type AsDegrees();
	type AsDegrees() const;
	StaticAngle& operator=(const StaticAngle& other);
	StaticAngle& operator=( StaticAngle&& other) noexcept;

	StaticAngle operator+(const StaticAngle& other) const;

	StaticAngle operator-(const StaticAngle& other) const;

	StaticAngle& operator +=(const StaticAngle& other);

	StaticAngle& operator -=(const StaticAngle& other);

	StaticAngle operator*(const_reference_type factor) const;

	StaticAngle operator/(const_reference_type divider) const;

	StaticAngle& operator *=(const_reference_type factor);

	StaticAngle& operator /=(const_reference_type divider);

	bool operator==(const StaticAngle& other) const;

	bool operator!=(const StaticAngle& other) const;

	StaticAngleInterval<type, AngleInterval::value_min, AngleInterval::value_max> GetInterval() const;
private:
	StaticAngle(const type& radiant);
	type m_radiants;
};





template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval>::StaticAngle(): m_radiants(type{})
{}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval>::StaticAngle(const StaticAngle& other): m_radiants(other.m_radiants)
{}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval>::StaticAngle(StaticAngle&& other) noexcept: m_radiants(other.m_radiants)
{
	other.m_radiants = type{};
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
type StaticAngle<type, AngleInterval>::AsRadians()
{
	return AngleInterval::Normalize(m_radiants);
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
type StaticAngle<type, AngleInterval>::AsRadians() const
{
	return AngleInterval::Normalize(m_radiants);
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
type StaticAngle<type, AngleInterval>::AsDegrees()
{
	return AngleInterval::Normalize(m_radiants)* static_cast<type>(180) / Math::PI_V<type>;
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
type StaticAngle<type, AngleInterval>::AsDegrees() const
{
	return AngleInterval::Normalize(m_radiants)* static_cast<type>(180) / Math::PI_V<type>;
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval>& StaticAngle<type, AngleInterval>::operator=(const StaticAngle& other)
{
	m_radiants = other.m_radiants;
	return *this;
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval>& StaticAngle<type, AngleInterval>::operator=(StaticAngle&& other) noexcept
{
	m_radiants = other.m_radiants;
	other.m_radiants = type{};
	return *this;
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval> StaticAngle<type, AngleInterval>::operator+(const StaticAngle& other) const
{
	return StaticAngle(m_radiants + other.m_radiants);
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval> StaticAngle<type, AngleInterval>::operator-(const StaticAngle& other) const
{
	return StaticAngle(m_radiants - other.m_radiants);
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval>& StaticAngle<type, AngleInterval>::operator+=(const StaticAngle& other)
{
	m_radiants += other.m_radiants;
	return *this;
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval>& StaticAngle<type, AngleInterval>::operator-=(const StaticAngle& other)
{
	m_radiants -= other.m_radiants;
	return *this;
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval> StaticAngle<type, AngleInterval>::operator*(const_reference_type factor) const
{
	return StaticAngle(m_radiants * factor);
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval> StaticAngle<type, AngleInterval>::operator/(const_reference_type divider) const
{
	if (divider == 0)
		throw std::out_of_range("Imposible to divide by 0");
	return StaticAngle(m_radiants / divider);
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval>& StaticAngle<type, AngleInterval>::operator*=(const_reference_type factor)
{
	m_radiants *= factor;
	return *this;
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval>& StaticAngle<type, AngleInterval>::operator/=(const_reference_type divider)
{
	if (divider == 0)
		throw std::out_of_range("Imposible to divide by 0");
	m_radiants /= divider;
	return *this;
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
bool StaticAngle<type, AngleInterval>::operator==(const StaticAngle& other) const
{
	return Math::IsSameValue(m_radiants, other.m_radiants, Math::EPSILON_V<value_type>);
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
bool StaticAngle<type, AngleInterval>::operator!=(const StaticAngle& other) const
{
	return !Math::IsSameValue(m_radiants, other.m_radiants, Math::EPSILON_V<value_type>);
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngleInterval<type, AngleInterval::value_min, AngleInterval::value_max> StaticAngle<type, AngleInterval>::
GetInterval() const
{
	return Interval{};
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval>::StaticAngle(const type& radiant): m_radiants(radiant)
{}

template<typename type, typename AngleInterval > requires is_floating_type_v<type>
StaticAngle< type, AngleInterval> Degree(const type& degree)
{
	auto rad = degree * (Math::PI_V<type> / static_cast<type>(180));
	return StaticAngle< type, AngleInterval>(rad);
}

template<typename type, typename AngleInterval > requires is_floating_type_v<type>
StaticAngle< type, AngleInterval> Radiant(const type& radiant)
{
	return StaticAngle< type, AngleInterval>(radiant);
}