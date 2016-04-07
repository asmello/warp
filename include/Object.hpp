#ifndef Object_hpp
#define Object_hpp

#include "Identifier.hpp"

namespace warp
{
    template <class Tag>
    class Object
    {
    public:
        typedef Identifier<Tag, size_t, -1> ID;
        
        ID getID() const { return id; }
        
    protected:
        ID id;
    };
}

#endif /* Object_hpp */
