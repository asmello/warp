#ifndef Shader_hpp
#define Shader_hpp

#include <GL/glew.h>

#include <string>

namespace warp
{
    class Shader
    {
        friend class ShaderManager;
        
    private:
        GLuint shaderProgram;
        GLint compile(GLenum type, char *source);
        void link(GLint vertexShader, GLint fragmentShader);
        Shader();
        ~Shader();
        void loadFromFile(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);
        
    public:
        void bind();
        void validate();
        GLuint getNativeHandle() const;
        GLint getAttribLocation(const std::string& attributeName) const;
        GLint getUniformLocation(const std::string& uniformName) const;
    };
}

#endif /* Shader_hpp */
