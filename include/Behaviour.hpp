#ifndef Behaviour_hpp
#define Behaviour_hpp

#include "Object.hpp"
#include "Component.hpp"
#include "GameObject.hpp"

#include <vector>
#include <memory>

namespace warp
{
	class Behaviour : public Component, public Object<Behaviour>
	{
	public:
		Behaviour(GameObject::ID gameObject);

		virtual void Start() {} // First frame it is active
		virtual void Update() {} // Once every frame before animation
		virtual void LateUpdate() {} // Once every frame after animation
		virtual void OnEnable() {} // When enabled
		virtual void OnDisable() {} // When disabled
	};
}

#endif /* ResourceManager_hpp */