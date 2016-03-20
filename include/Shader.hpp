#ifndef Shader_hpp
#define Shader_hpp

#include <GL/glew.h>

#include <string>

namespace warp {
    class Shader {
    private:
        GLuint shaderProgram;
        
    public:
        ~Shader();
        bool loadFromFile(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);
        void bind();
        GLuint getNativeHandle() const;
        GLint getAttribLocation(const std::string& attributeName) const;
        GLint getUniformLocation(const std::string& uniformName) const;
    };
}

#endif /* Shader_hpp */
