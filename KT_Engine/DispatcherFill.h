#pragma once
#include "Dispacher.h"


//template<typename Arg,typename Args,typename Ctor>
//class testFunc;
//
//template<typename... Arg,typename... Arg2,typename... Ctor>
//class testFunc<typelist<Arg...>,typelist<Arg2...>,typelist<Ctor...>>
//{
//public:
//	using lhsList = typelist<Arg...>;
//	using rhsList = typelist<Arg2...>;
//	static constexpr size_t sizelhs = size_v<lhsList>;
//	static constexpr size_t sizerhs = size_v<rhsList>;
//	template<auto FN,bool mirror,typename Base,typename returnType,typename ... Args>
//	 void Apply(FNDispatcher<Base,Base,returnType,typelist<Args...>>& dispatcher)
//	{
//		for (size_t i = 0; i < sizelhs; ++i)
//		{
//			for (size_t j = 0; j < sizerhs ; ++j)
//			{
//				private_Aply<i, j, FN, mirror, Base, returnType, Args...>(dispatcher);
//			}
//		}
//		
//	}
//private:
//	template<size_t indexlhs,size_t indexrhs, auto FN, bool mirror, typename Base, typename returnType, typename ... Args>
//	static void private_Aply(FNDispatcher<Base, Base, returnType, typelist<Args...>>& dispatcher)
//	{
//		using lhstype = at_t<indexlhs, lhsList>;
//		using rhstype = at_t<indexrhs,rhsList>;
//		auto fn = [](lhstype& lhs, rhstype& rhs, Ctor... cotrs)->returnType
//			{
//				return FN(lhs, rhs, cotrs...);
//			};
//		dispatcher.template Add < lhstype, rhstype, fn, mirror>();
//	}
//};
//
