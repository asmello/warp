#ifndef ShaderManager_hpp
#define ShaderManager_hpp

#include "Singleton.hpp"
#include "ResourceManager.hpp"

#include <string>

namespace warp
{
    class Shader;

    class ShaderManager : public ResourceManager<Shader>, public Singleton<ShaderManager>
    {
    public:
        void setActive(Object<Shader>::ID id);
        std::shared_ptr<Shader> getActive();
        Object<Shader>::ID createFromFile(const std::string& vertexShaderFile,
                                          const std::string& fragmentShaderFile);
        
    private:
        Object<Shader>::ID activeID;
    };
}

#endif /* ShaderManager_hpp */
