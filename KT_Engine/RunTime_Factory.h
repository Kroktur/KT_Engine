#pragma once
#include <map>
#include <stdexcept>
#include "CreateStrategy.h"
#include "Typelist.h"

template< typename BaseType, template<typename> class CreateStrategy, typename ...CtorArgs> requires ValidStrategy < BaseType, CreateStrategy>
class ICreator
{
public:
    using returnTypes = typename CreateStrategy<BaseType>::returnTypes;
    virtual~ICreator() = default;
    virtual returnTypes Create(const CtorArgs&... args) = 0;
};

template< typename BaseType, template<typename> class CreateStrategy, typename DerivedType, typename ...CtorArgs> requires ValidStrategy < BaseType, CreateStrategy>
class ConcreteCreator : public ICreator<BaseType, CreateStrategy, CtorArgs...>
{
public:
    using returnTypes = typename ICreator<BaseType, CreateStrategy, CtorArgs...>::returnTypes;
    returnTypes Create(const CtorArgs&... args) override
    {
        return CreateStrategy<BaseType>::template Create<DerivedType>(args...);
    }
};

template<typename KeyType, typename BaseType, template<typename> class CreateStrategy, typename list = typelist<>> requires ValidStrategy < BaseType, CreateStrategy>
class RT_Factory;

template<typename KeyType, typename BaseType, template<typename> class CreateStrategy, typename ...CtorArgs>
class RT_Factory<KeyType, BaseType, CreateStrategy, typelist<CtorArgs...>>
{
public:
    using returnTypes = typename CreateStrategy<BaseType>::returnTypes;
    ~RT_Factory() = default;
    template<typename Derived>
    void Register(const KeyType& key) requires std::is_base_of_v<BaseType, Derived>
    {
        if (m_map.find(key) != m_map.end())
            throw std::runtime_error("key Already Regiter");
        m_map[key] = std::make_unique<ConcreteCreator<BaseType, CreateStrategy, Derived, CtorArgs...>>() ;
    }
    returnTypes Create(const KeyType& key, const CtorArgs&... args)
    {
        if (m_map.find(key) == m_map.end())
            throw std::runtime_error("key not Regiter");
        return m_map[key]->Create(args...);
    }
private:
    std::map<KeyType,std::unique_ptr< ICreator<BaseType, CreateStrategy, CtorArgs...>>> m_map;
};

template<typename KeyType, typename BaseType, typename list = typelist<>>
using RT_Pointer_Factory = RT_Factory<KeyType, BaseType, Pointer, list>;

template<typename KeyType, typename BaseType, typename list = typelist<>>
using RT_UniquePointer_Factory = RT_Factory<KeyType, BaseType, UniquePointer, list>;

template<typename KeyType, typename BaseType, typename list = typelist<>>
using RT_SharedPointer_Factory = RT_Factory<KeyType, BaseType, SharedPointer, list>;
