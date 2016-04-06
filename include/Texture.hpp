#ifndef Texture_hpp
#define Texture_hpp

#include <Memory>
#include <GL/glew.h>

#include <string>

namespace warp
{
    class Texture
    {
        friend class TextureManager;
        
    private:
        GLenum target;
        GLuint txo;
        GLint uniSampler;
        bool initialized, loaded;
        
        void loadFromFile(const std::string& filename);
        
    public:
        // These constructors should not be used directly
        Texture(GLenum target);
         ~Texture();
        
        void bind();
    };
}

#endif /* Texture_hpp */
