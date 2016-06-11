#ifndef Texture_hpp
#define Texture_hpp

#include "Object.hpp"

#include <GL/glew.h>

#include <string>
#include <memory>
#include <vector>

namespace warp
{
    class Texture : public Object<Texture>
    {
        friend class TextureManager;
        
    private:
        GLenum target;
        GLuint txo;
        GLint uniSampler;
        bool initialized, loaded;
        
        void load2D(const std::string& path);
        void loadCubemap(const std::string& path);
        void loadCubemapFromMultiple(const std::vector<std::string>& paths);
        
    public:
        // These constructors should not be used directly
        Texture(GLenum target);
         ~Texture();
        
        void bind();
    };
}

#endif /* Texture_hpp */
