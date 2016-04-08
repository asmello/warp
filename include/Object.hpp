#ifndef Object_hpp
#define Object_hpp

#include "Identifier.hpp"

#include <limits>

namespace warp
{
    template <class Tag>
    class Object
    {
    public:
        typedef Identifier<Tag, std::size_t, std::numeric_limits<size_t>::max()> ID;
        
        ID getID() const { return id; }
        
    protected:
        ID id;
    };
}

#endif /* Object_hpp */
