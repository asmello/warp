#ifndef Material_hpp
#define Material_hpp

#include "Texture.hpp"
#include "Shader.hpp"

#include <memory>

namespace warp
{
    class Material
    {
    private:
        std::shared_ptr<Shader> shader;
        std::shared_ptr<Texture> texture;
    public:
        Material(std::shared_ptr<Shader>, std::shared_ptr<Texture>);
        std::shared_ptr<Shader> getShader();
        void bind();
    };
}

#endif /* Material_hpp */
