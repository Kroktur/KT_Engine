#pragma once
#include "Matrix.h"

template<typename type,size_t size>
class SquareMatrix : Matrix<type,size>
{
public:
	SquareMatrix() : Matrix<type,size,size>(){}
	SquareMatrix(const SquareMatrix& other) : Matrix<type, size, size>(other) {}
	SquareMatrix(const std::initializer_list <value_type>& list) : Matrix<type, size, size>(list){}
	template<typename... Args>
		SquareMatrix(const Args&... types) : Matrix<type, size, size>(types...) {}
	SquareMatrix(SquareMatrix&& other) noexcept : Matrix<type, size, size>(std::move(other)){}
	~SquareMatrix() = default;
};
