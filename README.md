# templated component pattern
A header-only implementation of a type-safe, cache-friendly template component pattern within a component-based architecture.
The code is small but applicable in commercial game development, and it's always expandable.

# Requirement
A compiler supporting C++20 

# Full code
```cpp
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
```

# Usage
```cpp
class Player;
class FSMComponent : ComponentBase<Player>
{
public:
	void foo()
	{
	}
};

class AnimationComponent : ComponentBase<Player>
{
public:
	void update()
	{
		// Decouple your  contents code.
		// Access different components if need.
		getOwner().getComponent<FSMComponent>().foo();
	}
};

class Player : public ComponentOwner<Player,
	FSMComponent,
	AnimationComponent>
{
public:
	Player() : ComponentOwner(*this)
	{}

	void foo()
	{
		getComponent<AnimationComponent>().update();
	}
};
```

# Recommendation
Direct referencing between components can lead to increased coupling. Make your own system. (e.g. messaging system)
