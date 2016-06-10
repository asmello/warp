#ifndef Behaviour_hpp
#define Behaviour_hpp

#include "Object.hpp"
#include "Component.hpp"
#include "Scene.hpp"

#include <vector>
#include <memory>

namespace warp
{
	class Behaviour : public ComponentImplementation<Behaviour>
	{
	public:
		Behaviour();

		virtual void Start() {} // TODO [First frame it is active]
		virtual void Update() {} // TODO [Once every frame before animation]
		virtual void LateUpdate() {} // TODO [Once every frame after animation]
		virtual void OnEnable() {} // TODO [When enabled]
		virtual void OnDisable() {} // TODO [When disabled]
	};
}

#endif /* ResourceManager_hpp */