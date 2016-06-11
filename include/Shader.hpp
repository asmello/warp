#ifndef Shader_hpp
#define Shader_hpp

#include "Object.hpp"

#include <GL/glew.h>

#include <string>
#include <vector>

namespace warp
{
    class Shader : public Object<Shader>
    {
        friend class ShaderManager;
        
    private:
        GLuint shaderProgram;
        GLint compile(GLenum type, char *source);
        const char * typeString(GLenum type);
        void link(GLint vertexShader, GLint fragmentShader);
        void loadFromFile(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);
        
    public:
        ~Shader();
        
        void bind();
        void validate();
        GLuint getNativeHandle() const;
        GLint getAttribLocation(const std::string& attributeName) const;
        GLint getUniformLocation(const std::string& uniformName) const;
        void setUniformBlockBinding(const std::string& uniformBlockName, GLint location);
        std::vector<std::string> getUniformBlockNames() const;
    };
}

#endif /* Shader_hpp */
