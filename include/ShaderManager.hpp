#ifndef ShaderManager_hpp
#define ShaderManager_hpp

#include "Singleton.hpp"
#include "Shader.hpp"

#include <string>
#include <memory>

namespace warp
{
    class ShaderManager : public Singleton<ShaderManager>
    {
    public:
        using ID = int;
        
        std::weak_ptr<Shader> getActive();
        std::weak_ptr<Shader> get(ID id);
        ID add(std::shared_ptr<Shader> shader);
        ID createFromFile(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
    };
}

#endif /* ShaderManager_hpp */
