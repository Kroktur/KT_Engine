#pragma once
#include <vector>
#include <map>


// lvl 1

//struct Component
//{
//	static int id;
//};
//
//struct go
//{
//	template<typename type>
//	void AddComponent()
//	{
//		m_components.push_back(new type{});
//	}
//	template<typename type>
//	type* GetComponent()
//	{
//		for (auto i : m_components)
//			if (i->id == type::id)
//				return i;
//		return nullptr;
//	}
//private:
//
//	static std::vector<Component*> m_components;
//};

// lvl 2
//template<typename type>
//int GetRtti2()
//{
//	static int toto = 0;
//	return toto++;
//}
//
//
//template<typename type>
//int GetRtti()
//{
//	static int toto = GetRtti2<type>();
//	return toto;
//}
//
//template<typename type>
//class ComponentContainer
//{
//public:
//	static void AddComponent(int id)
//	{
//		auto component = new type{};
//		auto it = m_components.find(id);
//		if (it == m_components.end())
//			m_components[id] = (component);
//		else
//			throw;
//	}
//	static type* find(int id)
//	{
//		auto it = m_components.find(id);
//		if (it != m_components.end())
//			return it->second;
//		return nullptr;
//	}
//private:
//	static std::map<int, type*> m_components;
//};
//template<typename type>
//std::map<int, type*> ComponentContainer<type>::m_components = std::map<int, type*>{};
//
//struct ComponentManager
//{
//public:
//	template<typename type>
//		void AddComponent()
//		{
//			auto id = GetRtti<type>();
//			m_idsComponent[GetRtti<type>()] = id;
//			ComponentContainer<type>::AddComponent(id);
//		}
//		template<typename type>
//		type* GetComponent()
//		{
//			auto it = m_idsComponent.find(GetRtti<type>());
//			if (it != m_idsComponent.end())
//				return ComponentContainer<type>::find(it->second);
//			return nullptr;
//		}
//private:
//	std::map<int,int> m_idsComponent;
//};

// TODO Lvl 3 : secure Component and RTTI

//TODO lvl 4 : type perfection

