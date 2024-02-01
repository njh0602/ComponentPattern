#pragma once

#include <type_traits>
#include <concepts>

template<typename Owner>
class ComponentBase
{
public:
	ComponentBase(Owner& owner) : _owner(owner)
	{
	}

	Owner& getOwner()
	{
		return _owner;
	}

protected:
	Owner& _owner{};
};

template<typename Owner, typename ... Components>
class ComponentOwner : public Components ...
{
public:
	ComponentOwner(Owner& owner) : Components(owner)...
	{
	}

	template<typename Component> requires std::disjunction_v<std::is_same<Component, Components>...>
	Component& getComponent()
	{
		return static_cast<Component&>(*this);
	}
};
