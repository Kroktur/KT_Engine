#pragma once
#include "PrimaryType_Category.h"

namespace Math
{
	template<typename type>
	static constexpr type EPSILON_V = 1e-15L;
	static constexpr long double EPSILON_LONG_DOUBLE = EPSILON_V<long double>;

	template<>
	constexpr double EPSILON_V<double> = 1e-12;
	static constexpr double EPSILON_DOUBLE = EPSILON_V<double>;

	template<>
	constexpr float EPSILON_V<float> = 1e-6f;
	static constexpr float EPSILON_FLOAT = EPSILON_V<float>;


	template<typename type>
static constexpr type PI_V = 3.141592653589793238462643383279L;
static constexpr long double PI_LD = PI_V<long double>;

template<>
 constexpr double PI_V<double> = 3.141592653589793238462643383279;
 static constexpr double PI_D = PI_V<double>;

template<>
 constexpr float PI_V<float> = 3.141593f;
 static constexpr float PI = PI_V<float>;




template<typename type> requires is_floating_type_v<type> || is_integral_type_v<type>
type AbsoluteValue(const type& value)
{
	return (value < static_cast<type>(0)) ? -value : value ; 
}

template<typename type> requires is_floating_type_v<type>
bool IsSameValue(const type& lhs ,const type& rhs,const type& EPSILON)
{
	return AbsoluteValue(lhs - rhs) < EPSILON;
}
template<typename type> requires is_integral_type_v<type>
bool IsSameValue(const type& lhs, const type& rhs)
{
	return lhs == rhs;
}

template<typename type> requires is_floating_type_v<type>
bool IsNull(const type& lhs, const type& EPSILON)
{
	return IsSameValue<type>(lhs,static_cast<type>(0),EPSILON) ;
}
template<typename type> requires is_integral_type_v<type>
bool IsNull(const type& lhs)
{
	return IsSameValue(lhs, static_cast<type>(0));
}
}