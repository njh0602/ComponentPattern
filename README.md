# ComponentPattern
A type-safe, cache-friendly template component pattern implementation.
The code is small but applicable in practical development, and it's always expandable.

# Usage
```
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
