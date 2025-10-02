#pragma once
#include <type_traits>
#include "CreateStrategy.h"
#include "Typelist.h"

template<typename BaseType, template<typename> class CreateStrategy, typename list = typelist<>>  requires ValidStrategy < BaseType, CreateStrategy>
struct CT_Factory_Cast;

template<typename BaseType, template<typename> class CreateStrategy, typename... Arg> requires (... && std::is_base_of_v<BaseType, Arg>)
struct CT_Factory_Cast<BaseType, CreateStrategy, typelist<Arg...>>
{
	template<typename DerivedType, typename ...Args> requires contains_v<DerivedType, typelist<Arg...>>
	static typename CreateStrategy<DerivedType>::returnTypes Create(const Args&... args)
	{
		return CreateStrategy<DerivedType>::template Create<DerivedType>(args...);
	}
	template<size_t index, typename ...Args> requires (size_v<typelist<Arg...>> > index)
		static typename CreateStrategy<at_t<index, typelist<Arg...>>>::returnTypes Create(const Args&... args)
	{

		return CreateStrategy<at_t<index, typelist<Arg...>>>::template Create<at_t<index, typelist<Arg...>>>(args...);
	}
};

template<typename KeyType, typename BaseType, typename list = typelist<>>
using CT_Static_Factory_Cast = CT_Factory_Cast< BaseType, Static, list>;

template<typename KeyType, typename BaseType, typename list = typelist<>>
using CT_Reference_Factory_Cast = CT_Factory_Cast< BaseType, Reference, list>;

template<typename KeyType, typename BaseType, typename list = typelist<>>
using CT_Pointer_Factory_Cast = CT_Factory_Cast< BaseType, Pointer, list>;

template<typename KeyType, typename BaseType, typename list = typelist<>>
using CT_UniquePointer_Factory_Cast = CT_Factory_Cast< BaseType, UniquePointer, list>;

template<typename KeyType, typename BaseType, typename list = typelist<>>
using CT_SharedPointer_Factory_Cast = CT_Factory_Cast< BaseType, SharedPointer, list>;

template<typename BaseType, template<typename> class CreateStrategy, typename list = typelist<>>  requires ValidStrategy < BaseType, CreateStrategy>
struct CT_Factory;

template<typename BaseType, template<typename> class CreateStrategy, typename... Arg> requires (... && std::is_base_of_v<BaseType, Arg>)
struct CT_Factory<BaseType, CreateStrategy, typelist<Arg...>>
{
	using returnTypes = typename CreateStrategy<BaseType>::returnTypes;
	template<typename DerivedType, typename ...Args> requires contains_v<DerivedType, typelist<Arg...>>
	static returnTypes Create(const Args&... args)
	{
		return CreateStrategy<BaseType>::template Create<DerivedType>(args...);
	}
	template<size_t index, typename ...Args> requires (size_v<typelist<Arg...>> > index)
		static returnTypes Create(const Args&... args)
	{

		return CreateStrategy<BaseType>::template Create<at_t<index, typelist<Arg...>>>(args...);
	}
};

template<typename KeyType, typename BaseType, typename list = typelist<>>
using CT_Pointer_Factory = CT_Factory< BaseType, Pointer, list>;

template<typename KeyType, typename BaseType, typename list = typelist<>>
using CT_UniquePointer_Factory = CT_Factory< BaseType, UniquePointer, list>;

template<typename KeyType, typename BaseType, typename list = typelist<>>
using CT_SharedPointer_Factory = CT_Factory< BaseType, SharedPointer, list>;
