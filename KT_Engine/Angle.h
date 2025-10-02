#pragma once
#include "AngleInterval.h"
template<typename type> requires is_floating_type_v<type>
class Angle;

template<typename type> requires is_floating_type_v<type>
Angle< type> Degree(const type& degree, const AngleInterval<type>& interval);

template<typename type> requires is_floating_type_v<type>
Angle < type> Radiant(const type& radiant, const AngleInterval<type>& interval);

template<typename type> requires is_floating_type_v<type>
class Angle
{
public:
	friend Angle Degree<type>(const type&, const AngleInterval<type>&);
	friend Angle Radiant<type>(const type&, const AngleInterval<type>&);
	using value_type = type;
	using pointer_type = type*;
	using const_pointer_type = const type*;
	using reference_type = type&;
	using const_reference_type = const type&;

	Angle( const AngleInterval<type>& strategy = UnsignedInterval<type>{});
	~Angle() = default;
	Angle(const Angle& other);

	Angle(Angle&& other) noexcept;

	type AsRadians();

	type AsRadians() const;

	type AsDegrees();

	type AsDegrees() const;

	Angle& operator=(const Angle& other);

	Angle& operator=(Angle&& other) noexcept;

	void SetInterval(const AngleInterval<type>& strategy);

	AngleInterval<type> GetInterval() const;

	Angle operator+(const Angle& other) const;

	Angle operator-(const Angle& other) const;

	Angle& operator +=(const Angle& other);

	Angle& operator -=(const Angle& other);

	Angle operator*(const_reference_type factor) const;

	Angle operator/(const_reference_type divider) const;

	Angle& operator *=(const_reference_type factor);

	Angle& operator /=(const_reference_type divider);

	bool operator==(const Angle& other) const;

	bool operator!=(const Angle& other) const;

private:
	Angle(const type& radiant, const AngleInterval<type>& interval);
	type m_radiants;
	AngleInterval<type> m_strategy;
};


template <typename type> requires is_floating_type_v<type>
Angle<type> Degree(const type& degree, const AngleInterval<type>& interval)
{
	auto rad = degree * (Math::PI_V<type> / static_cast<type>(180));
	return Angle<type>(rad, interval);
}



template <typename type> requires is_floating_type_v<type>
Angle<type> Radiant(const type& radiant, const AngleInterval<type>& interval)
{
	return Angle<type>(radiant, interval);
}

template <typename type> requires is_floating_type_v<type>
Angle<type>::Angle(const AngleInterval<type>& strategy):m_radiants(type{}), m_strategy(strategy)
{}

template <typename type> requires is_floating_type_v<type>
Angle<type>::Angle(const Angle& other):m_radiants(other.m_radiants),m_strategy(other.m_strategy)
{}

template <typename type> requires is_floating_type_v<type>
Angle<type>::Angle(Angle&& other) noexcept: m_radiants(other.m_radiants), m_strategy(std::move(other.m_strategy))
{
	other.m_radiants = type{};
	other.m_strategy = AngleInterval<type>{};
}

template <typename type> requires is_floating_type_v<type>
type Angle<type>::AsRadians()
{
	return m_radiants;
}

template <typename type> requires is_floating_type_v<type>
type Angle<type>::AsRadians() const
{
	return m_strategy.Normalize(m_radiants);
}

template <typename type> requires is_floating_type_v<type>
type Angle<type>::AsDegrees()
{
	return m_radiants * static_cast<type>(180) / Math::PI_V<type>;
}

template <typename type> requires is_floating_type_v<type>
type Angle<type>::AsDegrees() const
{
	return m_radiants * static_cast<type>(180) / Math::PI_V<type>;
}

template <typename type> requires is_floating_type_v<type>
Angle<type>& Angle<type>::operator=(const Angle& other)
{
	m_radiants = other.m_radiants;
	m_strategy = other.m_strategy;
	return *this;
}

template <typename type> requires is_floating_type_v<type>
Angle<type>& Angle<type>::operator=(Angle&& other) noexcept
{
	m_radiants = other.m_radiants;
	other.m_radiants = type{};
	m_strategy = std::move(other.m_strategy);
	other.m_strategy = AngleInterval<type>{};
	return *this;
}

template <typename type> requires is_floating_type_v<type>
void Angle<type>::SetInterval(const AngleInterval<type>& strategy)
{
	m_strategy = strategy;
	m_radiants = m_strategy.Normalize(m_radiants);
}

template <typename type> requires is_floating_type_v<type>
AngleInterval<type> Angle<type>::GetInterval() const
{
	return m_strategy;
}

template <typename type> requires is_floating_type_v<type>
Angle<type> Angle<type>::operator+(const Angle& other) const
{
	return Angle(m_radiants + other.m_radiants, m_strategy);
}

template <typename type> requires is_floating_type_v<type>
Angle<type> Angle<type>::operator-(const Angle& other) const
{
	return Angle(m_radiants - other.m_radiants, m_strategy);
}

template <typename type> requires is_floating_type_v<type>
Angle<type>& Angle<type>::operator+=(const Angle& other)
{
	m_radiants = m_strategy.Normalize(m_radiants + other.m_radiants);
	return *this;
}

template <typename type> requires is_floating_type_v<type>
Angle<type>& Angle<type>::operator-=(const Angle& other)
{
	m_radiants = m_strategy.Normalize(m_radiants - other.m_radiants);
	return *this;
}

template <typename type> requires is_floating_type_v<type>
Angle<type> Angle<type>::operator*(const_reference_type factor) const
{
	return Angle(m_radiants * factor);
}

template <typename type> requires is_floating_type_v<type>
Angle<type> Angle<type>::operator/(const_reference_type divider) const
{
	if (divider == 0)
		throw std::out_of_range("Imposible to divide by 0");
	return Angle(m_radiants / divider);
}

template <typename type> requires is_floating_type_v<type>
Angle<type>& Angle<type>::operator*=(const_reference_type factor)
{
	m_radiants = m_strategy.Normalize(m_radiants * factor);
	return *this;
}

template <typename type> requires is_floating_type_v<type>
Angle<type>& Angle<type>::operator/=(const_reference_type divider)
{
	if (divider == 0)
		throw std::out_of_range("Imposible to divide by 0");
	m_radiants = m_strategy.Normalize(m_radiants / divider);
	return *this;
}

template <typename type> requires is_floating_type_v<type>
bool Angle<type>::operator==(const Angle& other) const
{
	return Math::IsSameValue(m_radiants, other.m_radiants, Math::EPSILON_V<value_type>) && m_strategy == other.m_strategy;
}

template <typename type> requires is_floating_type_v<type>
bool Angle<type>::operator!=(const Angle& other) const
{
	return !Math::IsSameValue(m_radiants, other.m_radiants, Math::EPSILON_V<value_type>) || m_strategy != other.m_strategy;
}

template <typename type> requires is_floating_type_v<type>
Angle<type>::Angle(const type& radiant, const AngleInterval<type>& interval): m_radiants(radiant),m_strategy(interval)
{
	m_radiants = m_strategy.Normalize(radiant);
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
	return m_radiants;
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
type StaticAngle<type, AngleInterval>::AsRadians() const
{
	return m_radiants;
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
type StaticAngle<type, AngleInterval>::AsDegrees()
{
	return m_radiants * static_cast<type>(180) / Math::PI_V<type>;
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
type StaticAngle<type, AngleInterval>::AsDegrees() const
{
	return m_radiants * static_cast<type>(180) / Math::PI_V<type>;
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
	m_radiants = AngleInterval::Normalize(m_radiants + other.m_radiants);
	return *this;
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval>& StaticAngle<type, AngleInterval>::operator-=(const StaticAngle& other)
{
	m_radiants = AngleInterval::Normalize(m_radiants - other.m_radiants);
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
	m_radiants = AngleInterval::Normalize(m_radiants * factor);
	return *this;
}

template <typename type, typename AngleInterval> requires is_floating_type_v<type>
StaticAngle<type, AngleInterval>& StaticAngle<type, AngleInterval>::operator/=(const_reference_type divider)
{
	if (divider == 0)
		throw std::out_of_range("Imposible to divide by 0");
	m_radiants = AngleInterval::Normalize(m_radiants / divider);
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
{
	m_radiants = AngleInterval::Normalize(m_radiants);
}

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