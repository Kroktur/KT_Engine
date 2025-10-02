#pragma once
#include "Typelist.h"
#include <map>
#include <string>
#include <functional>
#include <stdexcept>

template<typename LhsType , typename RhsType = LhsType,typename ReturnType = void,typename Args = typelist<>>
class Dispatcher;


template<typename LhsType,typename RhsType, typename ReturnType, typename... Args>
class Dispatcher<LhsType,RhsType,ReturnType, typelist<Args...>>
{
public:
	using key_type = std::pair<std::string, std::string>;
	using value_type = std::function<ReturnType(LhsType&, RhsType&, const Args&...)>;
	template<typename DerivedLhsType,typename DerivedRhsType>
	void Add(const value_type& value)
	{
		key_type key = key_type(typeid(DerivedLhsType).name(), typeid(DerivedRhsType).name());
		auto it = m_map.find(key);
		if (it != m_map.end())
			throw std::runtime_error("Already Register");
		m_map[key] = value;

	}
	ReturnType operator()(LhsType& lhs, RhsType& rhs,const Args&... args)
	{
		key_type key = key_type(typeid(lhs).name(), typeid(rhs).name());
		auto it = m_map.find(key);
		if (it == m_map.end())
			throw std::runtime_error("not Register");
		return it->second(lhs,rhs,args...);

	}
private:
	std::map<key_type,value_type> m_map;
};

template<typename LhsType, typename RhsType = LhsType, typename ReturnType = void, typename Args = typelist<>>
class FNDispatcher;


template<typename LhsType, typename RhsType, typename ReturnType, typename... Args>
class FNDispatcher<LhsType, RhsType, ReturnType, typelist<Args...>>
{
public:
	using CtorList = typelist<Args...>;
	template<typename DerivedLhsType, typename DerivedRhsType,ReturnType(*FN)(DerivedLhsType&, DerivedRhsType&, Args...), bool Miror = false>
	void Add()
	{
		auto fn = [&](LhsType& lhs, RhsType& rhs, const Args&... args)->ReturnType
			{
				return FN(static_cast<DerivedLhsType&>(lhs), static_cast<DerivedRhsType&>(rhs), args...);
			};
		m_dispatcher.template Add<DerivedLhsType,DerivedRhsType>(fn);

		if constexpr (!Miror)
			return;
		auto fn2 = [&](RhsType& rhs, LhsType& lhs, const Args&... args) ->ReturnType
			{
				return fn(lhs, rhs,args...);
			};
		m_dispatcher.template Add<DerivedRhsType, DerivedLhsType>(fn2);
	}
	ReturnType operator()(LhsType& lhs, RhsType& rhs,const Args&... args)
	{
		return m_dispacher(lhs, rhs , args...);
	}
private:
	Dispatcher<LhsType, RhsType, ReturnType, CtorList> m_dispatcher;
};
