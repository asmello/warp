//
//  Texture.hpp
//  Warp
//
//  Created by André Sá de Mello on 3/18/16.
//
//

#ifndef Texture_hpp
#define Texture_hpp

#include <GL/glew.h>

#include <string>

namespace warp {
    class Texture {
    private:
        GLenum target;
        GLuint txo;
        
    public:
        Texture(GLenum target);
        ~Texture();
        void loadFromFile(const std::string& filename);
        void bind(GLenum TextureUnit);
    };
}

#endif /* Texture_hpp */
