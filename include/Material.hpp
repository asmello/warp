#ifndef Material_hpp
#define Material_hpp

#include "TextureManager.hpp"
#include "ShaderManager.hpp"

#include <memory>

namespace warp
{
    class Material
    {
        friend class MaterialManager;
        
    private:
        TextureID textureID;
        ShaderID shaderID;
        
    public:
        // These constructors should not be used directly
        Material(TextureID texture, ShaderID shader);
        
        ShaderID getShader();
        void bind();
    };
}

#endif /* Material_hpp */
