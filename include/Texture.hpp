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
        Texture(GLenum target);
        void loadFromFile(const std::string& filename);
        ~Texture();
        
    public:
        void init();
        void bind();
    };
}

#endif /* Texture_hpp */
