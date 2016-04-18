#ifndef Material_hpp
#define Material_hpp

#include "Object.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

#include <vector>
#include <memory>
#include <initializer_list>

namespace warp
{
    class Material : public Object<Material>
    {
        friend class MaterialManager;
        
    private:
        Shader::ID shaderID;
        std::vector<Texture::ID> textureIDs;
        
    public:
        // These constructors should not be used directly
        Material(Texture::ID texture, Shader::ID shader);
        Material(std::vector<Texture::ID> textures, Shader::ID shader);
        Material(std::initializer_list<Texture::ID> textures, Shader::ID shader);
        
        Shader::ID getShader();
        void bind();
    };
}

#endif /* Material_hpp */
