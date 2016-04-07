#ifndef Material_hpp
#define Material_hpp

#include "Object.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

#include <memory>

namespace warp
{
    class Material : public Object<Material>
    {
        friend class MaterialManager;
        
    private:
        Texture::ID textureID;
        Shader::ID shaderID;
        
    public:
        // These constructors should not be used directly
        Material(Texture::ID texture, Shader::ID shader);
        
        Shader::ID getShader();
        void bind();
    };
}

#endif /* Material_hpp */
