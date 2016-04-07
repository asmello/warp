#ifndef ShaderManager_hpp
#define ShaderManager_hpp

#include "Identifier.hpp"
#include "Singleton.hpp"
#include "Shader.hpp"

#include <vector>
#include <memory>
#include <string>

namespace warp
{
    struct shader_tag{}; // Magic strong typedefness
    typedef Identifier<shader_tag, int, -1> ShaderID;
    
    class ShaderManager : public Singleton<ShaderManager>
    {
    public:
        void setActive(ShaderID id);
        std::shared_ptr<Shader> getActive();
        std::shared_ptr<Shader> get(ShaderID id);
        ShaderID add(std::shared_ptr<Shader> shader);
        ShaderID createFromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
        
    private:
        std::vector<std::shared_ptr<Shader>> shaders;
        ShaderID activeID;
    };
}

#endif /* ShaderManager_hpp */
