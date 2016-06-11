#ifndef Renderer_hpp
#define Renderer_hpp

#include "Object.hpp"
#include "Component.hpp"

#include <vector>
#include <memory>
#include <limits>

namespace warp
{
    class Renderer : public ComponentImplementation<Renderer>
    {
    public:
        Renderer() : active(true), priority(0) { }
        
        virtual void render() = 0;
        void activate() { active = true; }
        bool isActive() const { return active; }
        
        bool operator <(const Renderer& d) const
        {
            return priority < d.priority;
        }
        
        static void sort(std::vector<std::shared_ptr<Renderer>>& v)
        {
            std::sort(v.begin(), v.end(),
                      [](const std::shared_ptr<Renderer>& lhs, const std::shared_ptr<Renderer>& rhs){
                          return lhs->priority < rhs->priority;
                      });
        }
        
        int getPriority() const { return priority; }
        void setPriority(int priority) { this->priority = priority; }
        
        const int MAX_PRIORITY = std::numeric_limits<int>::lowest();
        const int MIN_PRIORITY = std::numeric_limits<int>::max();
        
    protected:
        bool active;
        int priority;
    };
}

#endif /* Renderer_hpp */
