#ifndef Behaviour_hpp
#define Behaviour_hpp

#include "Object.hpp"
#include "Component.hpp"
#include "Scene.hpp"

#include <vector>
#include <memory>

namespace warp
{
	class Behavior : public ComponentImplementation<Behavior>
	{
	public:
		virtual void start() {} // TODO [First frame it is active]
		virtual void update() {} // TODO [Once every frame before animation]
		virtual void lateUpdate() {} // TODO [Once every frame after animation]
		virtual void onEnable() {} // TODO [When enabled]
		virtual void onDisable() {} // TODO [When disabled]
	};
}

#endif /* ResourceManager_hpp */