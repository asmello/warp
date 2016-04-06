#ifndef Material_hpp
#define Material_hpp

#include "TextureManager.hpp"
#include "ShaderManager.hpp"

#include <memory>

namespace warp
{
    class Material
    {
    private:
        TextureManager::ID texture;
        ShaderManager::ID shader;
    public:
        Material(ShaderManager::ID shader, TextureManager::ID texture);
        ShaderManager::ID getShader();
        void bind();
    };
}

#endif /* Material_hpp */
