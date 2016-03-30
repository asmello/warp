#ifndef Texture_hpp
#define Texture_hpp

#include "Shader.hpp"

#include <GL/glew.h>

#include <string>

namespace warp {
    class Texture {
    private:
        GLenum target;
        GLuint txo;
        GLint uniSampler;
        bool initialized, loaded;
        
    public:
        Texture(GLenum target);
        ~Texture();
        void init(const std::shared_ptr<const warp::Shader> shader);
        void loadFromFile(const std::string& filename);
        void bind();
    };
}

#endif /* Texture_hpp */
