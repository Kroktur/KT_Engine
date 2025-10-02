#pragma once
#include <cstddef>
#include "TypeTrait.h"
//is_void
template<typename type>
using is_void = is_same<type, void>;

template<typename type>
static constexpr bool is_void_v = is_void<type>::value;
//is_null_pointer
template<typename type>
using is_null_pointer = is_same<type, std::nullptr_t>;

template<typename type>
static constexpr bool is_null_pointer_v = is_null_pointer<type>::value;

//is_floating_type
template<typename type>
using is_floating_type = is_type_in_pack < remove_cv_t<type>
,float
,double
,long double>;

template<typename type>
static constexpr bool is_floating_type_v = is_floating_type<type>::value;

//is_integral_type
template<typename type>
using is_integral_type = is_type_in_pack < remove_cv_t<type>, bool
,char
,signed char
,unsigned char
, signed short
,unsigned short
,signed int
,unsigned int
,signed long
,unsigned long
,signed long long
,unsigned long long>;


template<typename type>
static constexpr bool is_integral_type_v = is_integral_type<type>::value;

//is_array
template<typename type>
struct is_array : false_type
{};
template<typename type ,size_t size>
struct is_array<type[size]> : true_type
{};
template<typename type>
struct is_array<type[]> : true_type
{};

template<typename type>
static constexpr bool is_array_v = is_array<remove_cv_t<type>>::value;

//is_pointer
template<typename type>
struct is_pointer : false_type
{};
template<typename type>
struct is_pointer<type*> : true_type
{};

template<typename type>
static constexpr bool is_pointer_v = is_pointer<remove_cv_t<type>>::value;


