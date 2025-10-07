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
class RTTI
{
public:
	template<typename type>
	static int GetTypeId()
	{
		static int id = m_id++;
		return id;
	}
	template <typename type>
	static int GetInstanceId()
	{
		static int id = 0;
		return id++;
	}
private:
	static int m_id;
};
int RTTI::m_id = 0;
template<typename type>
class ComponentContainer
{
public:
	template<typename... Args>
	static void AddComponent(int id,const Args&... args)
	{
		auto it = m_components.find(id);
		if (it == m_components.end())
			m_components[id] = std::make_unique<type>(args...);
		else
			throw std::runtime_error("component Already Exist");
	}
	static type* GetComponent(int id)
	{
		auto it = m_components.find(id);
		return (it != m_components.end()) ? it->second.get() : nullptr;
	}
	static void RemoveComponent(int id )
	{
		auto it = m_components.find(id);
		if (it == m_components.end())
			throw std::runtime_error("Doesn't exists");
		m_components.erase(it);
	}
private:
	static std::map<int, std::unique_ptr<type>> m_components;
};
template<typename type>
std::map<int, std::unique_ptr<type>> ComponentContainer<type>::m_components = std::map<int, std::unique_ptr<type>>{};

struct ComponentManager
{
public:
	template<typename type,typename... Args>
		void AddComponent(const Args&... args)
		{
		auto it = m_idsComponent.find(RTTI::GetTypeId<type>());
		if (it != m_idsComponent.end())
			throw std::runtime_error("Component Already Exists");
			auto id = RTTI::GetInstanceId<type>();
			m_idsComponent[RTTI::GetTypeId<type>()] = id;
			ComponentContainer<type>::AddComponent(id,args...);
		}
		template<typename type>
		type* GetComponent()
		{
			auto it = m_idsComponent.find(RTTI::GetTypeId<type>());
			return (it != m_idsComponent.end()) ? ComponentContainer<type>::GetComponent(it->second) : nullptr;
		}
		template<typename type>
		void RemoveComponent()
		{
			auto it = m_idsComponent.find(RTTI::GetTypeId<type>());
			if (it == m_idsComponent.end())
				throw std::runtime_error("Doesn't exists");
			ComponentContainer<type>::RemoveComponent(it->second);
			m_idsComponent.erase(it);
		}

		template<typename type,typename... Args>
		void RemplaceComponent(const Args&... args)
		{
			RemoveComponent<type>();
			AddComponent<type>(args...);
		}

		template<typename type>
		bool HasComponent() const
		{
			auto it = m_idsComponent.find(RTTI::GetTypeId<type>());
			return it != m_idsComponent.end();
		}
private:
	std::map<int,int> m_idsComponent;
};



//TODO lvl 4 : type perfection and secure Component

//TODO lvl 5 : pool and Optimisation