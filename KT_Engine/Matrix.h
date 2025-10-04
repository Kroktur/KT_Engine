#pragma once
#include "PrimaryType_Category.h"
#include <array>
#include <stdexcept>
#include "Math.h"
namespace detail
{
	template <typename type, size_t height, size_t width = height>
	concept MatrixAvailable = (height >= 1 && width >= 1) && (is_floating_type_v<type> || is_integral_type_v<type>);
}

template<typename type,size_t height,size_t width = height> requires detail::MatrixAvailable<type,height,width>
class Matrix
{
public:
	using value_type = type;
	using pointer_type = type*;
	using const_pointer_type = const type*;
	using reference_type = type&;
	using const_reference_type = const type&;
	static constexpr size_t size = height * width;

	Matrix();
	Matrix(const Matrix& other);
	Matrix(const std::initializer_list <value_type>& list);
	template<typename... Args> requires (sizeof...(Args) <=  height * width)
	Matrix(const Args&... types);
	Matrix(Matrix&& other) noexcept;
	~Matrix() = default;
	void Clear();
	static size_t Size();
	static size_t Height();
	static size_t Width();
	static size_t GetCellIndex(const size_t& row, const size_t& col);
	reference_type GetCell(const size_t& row, const size_t& col);
	const_reference_type GetCell(const size_t& row, const size_t& col) const;
	reference_type operator[](const size_t& index);
	reference_type At(const size_t& index);
	const_reference_type operator[](const size_t& index) const;
	const_reference_type At(const size_t& index)const;
	Matrix& operator=(const Matrix& other);
	Matrix& operator=(Matrix&& other) noexcept;
	bool operator==(const Matrix& other) const;
	bool operator!=(const Matrix& other) const;
	Matrix operator +(const Matrix& other) const;
	Matrix operator -(const Matrix& other) const;
	Matrix& operator +=(const Matrix& other);
	Matrix& operator -=(const Matrix& other);
	Matrix operator *(const type& factor) const;
	Matrix operator /(const type& divider) const;
	Matrix& operator *=(const type& factor);
	Matrix& operator /=(const type& divider);
	bool IsNull() const;
	template<size_t otherWidth>requires (otherWidth >= 1)
	Matrix<type, height, otherWidth> MatrixProduct(const Matrix<type, width, otherWidth>& other);
	Matrix<type,width,height> Transposition() const;

protected:
	std::array< type, size> m_data;
};

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width>::Matrix() : m_data(std::array< type, width* height>{}) {}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width>::Matrix(const Matrix& other) : m_data(other.m_data) {}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width>::Matrix(const std::initializer_list<value_type>& list) : m_data(std::array< type, width* height>{})
{
	if (list.size() > size)
		throw std::runtime_error("list too long for this Matrix");
	std::copy(list.begin(), list.end(), m_data);
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
template <typename ... Args> requires (sizeof...(Args) <= height * width)
Matrix<type, height, width>::Matrix(const Args&... types) : m_data(std::array<value_type, size>{types...}) {}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width>::Matrix(Matrix&& other) noexcept : m_data(other.m_data)
{

}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
void Matrix<type, height, width>::Clear()
{
	std::fill(m_data.begin(), m_data.end(), type{});
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
size_t Matrix<type, height, width>::Size()
{
	return size;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
size_t Matrix<type, height, width>::Height()
{
	return height;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
size_t Matrix<type, height, width>::Width()
{
	return  width;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
size_t Matrix<type, height, width>::GetCellIndex(const size_t& row, const size_t& col)
{
	auto index = row * width + col;
	if (index >= size)
		throw std::out_of_range("out of range");
	return index;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
typename Matrix<type, height, width>::reference_type Matrix<type, height, width>::GetCell(const size_t& row, const size_t& col)
{
	return m_data[GetCellIndex(row, col)];
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
typename Matrix<type, height, width>::const_reference_type Matrix<type, height, width>::GetCell(const size_t& row, const size_t& col) const
{
	return m_data[GetCellIndex(row, col)];
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
typename Matrix<type, height, width>::reference_type Matrix<type, height, width>::operator[](const size_t& index)
{
	return m_data[index];
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
typename Matrix<type, height, width>::reference_type Matrix<type, height, width>::At(const size_t& index)
{
	if (index >= size)
		throw std::runtime_error("index is too big ");
	return m_data.at(index);
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
typename Matrix<type, height, width>::const_reference_type Matrix<type, height, width>::operator[](const size_t& index) const
{
	return m_data[index];
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
typename Matrix<type, height, width>::const_reference_type Matrix<type, height, width>::At(const size_t& index) const
{
	if (index >= size)
		throw std::runtime_error("index is too big ");
	return m_data.at(index);
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width>& Matrix<type, height, width>::operator=(const Matrix& other)
{
	if (this != &other)
		m_data = other.m_data;
	return *this;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width>& Matrix<type, height, width>::operator=(Matrix&& other) noexcept
{
	m_data = std::move(other.m_data);
	return *this;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
bool Matrix<type, height, width>::operator==(const Matrix& other) const
{
	return m_data == other.m_data;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
bool Matrix<type, height, width>::operator!=(const Matrix& other) const
{
	return m_data != other.m_data;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width> Matrix<type, height, width>::operator+(const Matrix& other) const
{
	Matrix result;
	for (size_t i = 0; i <size; ++i)
	{
		result[i] = m_data[i] + other[i];
	}
	return  result;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width> Matrix<type, height, width>::operator-(const Matrix& other) const
{
	Matrix result;
	for (size_t i = 0; i < size; ++i)
	{
		result[i] = m_data[i] - other[i];
	}
	return  result;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width>& Matrix<type, height, width>::operator+=(const Matrix& other)
{
	for (size_t i = 0; i <size; ++i)
	{
		m_data[i] += other[i];
	}
	return  *this;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width>& Matrix<type, height, width>::operator-=(const Matrix& other)
{
	for (size_t i = 0; i < size; ++i)
	{
		m_data[i] -= other[i];
	}
	return  *this;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width> Matrix<type, height, width>::operator*(const type& factor) const
{
	Matrix result;
	for (size_t i = 0; i < size; ++i)
	{
		result[i] = m_data[i] * factor;
	}
	return result;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width> Matrix<type, height, width>::operator/(const type& divider) const
{
	if (divider == 0)
		throw std::out_of_range("can't divide by 0");
	Matrix result;
	for (size_t i = 0; i < size; ++i)
	{
		result[i] = m_data[i] / divider;
	}
	return  result;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width>& Matrix<type, height, width>::operator*=(const type& factor)
{
	for (size_t i = 0; i < size; ++i)
	{
		m_data[i] *= factor;
	}
	return *this;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, height, width>& Matrix<type, height, width>::operator/=(const type& divider)
{
	if (divider == 0)
		throw std::out_of_range("can't divide by 0");

	for (size_t i = 0; i < size; ++i)
	{
		m_data[i] /= divider;
	}
	return  *this;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
bool Matrix<type, height, width>::IsNull() const
{
	if constexpr (is_floating_type_v<value_type>)
	{
		value_type Epsilon = Math::EPSILON_V<value_type>;
		for (auto it : m_data)
		{
			if (!Math::IsNull<type>(it,Epsilon))
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

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
template <size_t otherWidth> requires (otherWidth >= 1)
Matrix<type, height, otherWidth> Matrix<type, height, width>::MatrixProduct(
	const Matrix<type, width, otherWidth>& other)
{
	Matrix<type, height, otherWidth> result;
	for (size_t row = 0; row < height; ++row)
	{
		for (size_t col = 0; col < otherWidth; ++col)
		{
			auto data = type{};
			for (size_t idx = 0; idx < width; ++idx)
				data += GetCell(row, idx) * other.GetCell(idx, col);
			result.GetCell(row, col) = data;
		}
	}
	return result;
}

template <typename type, size_t height, size_t width> requires detail::MatrixAvailable<type, height, width>
Matrix<type, width, height> Matrix<type, height, width>::Transposition() const
{
	Matrix<type, width, height> result;
	for (size_t row = 0; row < height; ++row)
	{
		for (size_t col = 0; col < width; ++col)
		{
			result.GetCell(col, row) = this->GetCell(row,col);
		}
	}
	return result;
}

template<typename type,size_t height,size_t width>
std::ostream& operator<< (std::ostream& os,const Matrix<type,height,width>& matrix)
{
	os << "Matrix: " << std::endl;
	if (matrix.Size() == 0)
	{
		os << "[ ]" << std::endl;
		return os;
	}
	for (auto i = 0; i < height; ++i)
	{
		os << "[";
		for (auto j = 0; j < width - 1; ++j)
		{
			os << matrix.GetCell(i, j) << " , ";
		}
		os << matrix.GetCell(i, width - 1) << "]" << std::endl;
	}
	return os;
}