#pragma once
#include <memory>


template<typename Type>
class Static
{
public:
    using returnTypes = Type;
    template<typename SameType, typename ...CtorArgs> requires std::is_same_v < Type, SameType >
    static returnTypes Create(const CtorArgs&... args)
    {
        return SameType{ args... };
    }

};

template<typename Type>
class Reference
{
public:
    using returnTypes = Type&;
    template<typename SameType, typename ...CtorArgs>  requires std::is_same_v < Type, SameType >
    static returnTypes Create(const CtorArgs&... args)
    {
        return SameType{ args... };
    }

};

template<typename BaseType>
class Pointer
{
public:
    using returnTypes = BaseType*;
    template<typename DerivedType, typename ...CtorArgs> requires std::is_base_of_v<BaseType, DerivedType>
    static returnTypes Create(const CtorArgs&... args)
    {
        return new DerivedType(args...);
    }
};

template<typename BaseType>
class UniquePointer
{
public:
    using returnTypes = std::unique_ptr<BaseType>;
    template<typename DerivedType, typename ...CtorArgs> requires std::is_base_of_v<BaseType, DerivedType>
    static returnTypes Create(const CtorArgs&... args)
    {
        return std::make_unique<DerivedType>(args...);
    }
};
template<typename BaseType>
class SharedPointer
{
public:
    using returnTypes = std::shared_ptr<BaseType>;
    template<typename DerivedType, typename ...CtorArgs> requires std::is_base_of_v<BaseType, DerivedType>
    static returnTypes Create(const CtorArgs&... args)
    {
        return std::make_shared<DerivedType>(args...);
    }
};


template<typename type, template<typename> class CreateStrategy>
concept ValidStrategy = requires
{
    typename CreateStrategy<type>::returnTypes;
};




