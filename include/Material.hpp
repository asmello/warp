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
        TextureManager::ID textureID;
        ShaderManager::ID shaderID;
        
    public:
        // These constructors should not be used directly
        Material(TextureManager::ID texture, ShaderManager::ID shader);
        
        ShaderManager::ID getShader();
        void bind();
    };
}

#endif /* Material_hpp */
