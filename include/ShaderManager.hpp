#ifndef ShaderManager_hpp
#define ShaderManager_hpp

#include "Singleton.hpp"
#include "Shader.hpp"

#include <vector>
#include <memory>
#include <string>

namespace warp
{
    class ShaderManager : public Singleton<ShaderManager>
    {
    public:
        void setActive(Shader::ID id);
        std::shared_ptr<Shader> getActive();
        std::shared_ptr<Shader> get(Shader::ID id);
        Shader::ID add(std::shared_ptr<Shader> shader);
        Shader::ID createFromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
        
    private:
        std::vector<std::shared_ptr<Shader>> shaders;
        Shader::ID activeID;
    };
}

#endif /* ShaderManager_hpp */
