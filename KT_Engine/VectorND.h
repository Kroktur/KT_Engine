#pragma once
#include <array>
#include <stdexcept>
#include "Math.h"
#include "PrimaryType_Category.h"

template<typename type,size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
class VectorND
{
public:
	using value_type = type;
	using pointer_type = type*;
	using const_pointer_type = const type*;
	using reference_type = type&;
	using const_reference_type = const type&;

	VectorND();
	VectorND(const VectorND& other);
	VectorND(const std::initializer_list<value_type>& list);
	template<typename ...Args>  requires (sizeof...(Args) <= size)
	VectorND(const Args&... types);
	VectorND(VectorND&& other) noexcept;
	~VectorND() = default;

	void Clear();
	VectorND& operator=(const VectorND& other);
	VectorND& operator=(VectorND&& other) noexcept;
	bool operator==(const VectorND& other) const;
	bool operator!=(const VectorND& other) const;
	static size_t Size();
	reference_type operator[](const size_t& index);
	reference_type At(const size_t& index);
	const_reference_type operator[](const size_t& index) const;
	const_reference_type At(const size_t& index)const;
	VectorND operator +(const VectorND& other) const;
	VectorND operator -(const VectorND& other) const;
	VectorND& operator +=(const VectorND& other);
	VectorND& operator -=(const VectorND& other);
	VectorND operator *(const_reference_type factor) const;
	VectorND operator /(const_reference_type divider) const;
	VectorND& operator *=(const_reference_type factor);
	VectorND& operator /=(const_reference_type divider);
	value_type NormSQRT() const;
	value_type Norm() const;
	bool IsNull() const;
	VectorND Normalize() const;
	value_type Dot(const VectorND& other) const;
protected:
	std::array<value_type, size> m_data;
};

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size>::VectorND() : m_data(std::array<value_type,size>{})
{
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size>::VectorND(const VectorND& other) : m_data(other.m_data)
{
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size>::VectorND(const std::initializer_list<value_type>& list): m_data(std::array<value_type, size>{})
{
	if (list.size() > size)
		throw std::runtime_error("list too long for this vectorND");
	std::copy(list.begin(), list.end(), m_data);
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
template <typename ... Args> requires (sizeof...(Args) <= size)
VectorND<type, size>::VectorND(const Args&... types) : m_data(std::array<value_type, size>{types...})
{

}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size>::VectorND(VectorND&& other) noexcept: m_data(std::move(other.m_data))
{
	
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
void VectorND<type, size>::Clear()
{
	std::fill(m_data.begin(), m_data.end(), type{});
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size>& VectorND<type, size>::operator=(const VectorND& other)
{
	if (this != &other)
		m_data = other.m_data;
	return *this;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size>& VectorND<type, size>::operator=(VectorND&& other) noexcept
{
	m_data = std::move(other.m_data);
	return *this;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
bool VectorND<type, size>::operator==(const VectorND& other) const
{
	return m_data == other.m_data;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
bool VectorND<type, size>::operator!=(const VectorND& other) const
{
	return m_data != other.m_data;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
size_t VectorND<type, size>::Size()
{
	return size;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
typename VectorND<type, size>::reference_type VectorND<type, size>::operator[](const size_t& index)
{
	return m_data[index];
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
typename VectorND<type, size>::reference_type VectorND<type, size>::At(const size_t& index)
{
	if (index >= size)
		throw std::runtime_error("index is too big ");
	return m_data.at(index);
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
typename VectorND<type, size>::const_reference_type VectorND<type, size>::operator[](const size_t& index) const
{
	return m_data[index];
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
typename VectorND<type, size>::const_reference_type VectorND<type, size>::At(const size_t& index) const
{
	if (index >= size)
		throw std::runtime_error("index is too big ");
	return m_data.at(index);
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size> VectorND<type, size>::operator+(const VectorND& other) const
{
	VectorND result;
	for (size_t i = 0; i < size; ++i)
	{
		result[i] = m_data[i] + other[i];
	}
	return  result;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size> VectorND<type, size>::operator-(const VectorND& other) const
{
	VectorND result;
	for (size_t i = 0; i < size; ++i)
	{
		result[i] = m_data[i] - other[i];
	}
	return  result;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size>& VectorND<type, size>::operator+=(const VectorND& other)
{
	for (size_t i = 0; i < size; ++i)
	{
		 m_data[i] += other[i];
	}
	return *this;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size>& VectorND<type, size>::operator-=(const VectorND& other)
{
	for (size_t i = 0; i < size; ++i)
	{
		m_data[i] -= other[i];
	}
	return  *this;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size> VectorND<type, size>::operator*(const_reference_type factor) const
{
	VectorND result;
	for (size_t i = 0; i < size; ++i)
	{
		result[i] = m_data[i] * factor;
	}
	return  result;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size> VectorND<type, size>::operator/(const_reference_type divider) const
{
	if (divider == 0)
		throw std::out_of_range("can't divide by 0");
	VectorND result;
	for (size_t i = 0; i < size; ++i)
	{
		result[i] = m_data[i] / divider;
	}
	return  result;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size>& VectorND<type, size>::operator*=(const_reference_type factor)
{
	for (size_t i = 0; i < size; ++i)
	{
		m_data[i] *= factor;
	}
	return  *this;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size>& VectorND<type, size>::operator/=(const_reference_type divider)
{
	if (divider == 0)
		throw std::out_of_range("can't divide by 0");

	for (size_t i = 0; i < size; ++i)
	{
		m_data[i] /= divider;
	}
	return  *this;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
typename VectorND<type, size>::value_type VectorND<type, size>::NormSQRT() const
{
	value_type result = type{};
	for (size_t i = 0; i < size; ++i)
	{
		result += m_data[i] * m_data[i];
	}
	return result;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
typename VectorND<type, size>::value_type VectorND<type, size>::Norm() const
{
	return std::sqrt(NormSQRT());
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
bool VectorND<type, size>::IsNull() const
{
	 if constexpr (is_floating_type_v<value_type>)
	{
		value_type Epsilon = Math::EPSILON_V<value_type>;
		for (auto it : m_data)
		{
			if (!Math::IsNull<type>(it, Epsilon))
				return false;
		}
	}
	else
	{
		for (auto it : m_data)
		{
			if (it != 0)
				return false;
		}
	}
	return true;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
VectorND<type, size> VectorND<type, size>::Normalize() const
{
	if (IsNull())
		throw std::runtime_error("can't normilize null vector");
	value_type length = Norm();
	return *this / length;
}

template <typename type, size_t size> requires is_floating_type_v<type> || is_integral_type_v<type>
typename VectorND<type, size>::value_type VectorND<type, size>::Dot(const VectorND& other) const
{
	value_type result = type{};
	for (size_t i = 0; i < size; ++i)
	{
		result += m_data[i] * other[i];
	}
	return result;
}



