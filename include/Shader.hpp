//
//  Shader.hpp
//  HelloGL
//
//  Created by André Sá de Mello on 3/10/16.
//  Copyright © 2016 André Sá de Mello. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <GL/glew.h>

#include <string>

class Shader {
private:
    GLuint shaderProgram;
  
public:
    ~Shader();
    bool loadFromFile(const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);
    void bind();
    GLuint getNativeHandle();
    GLint getAttribLocation(const std::string& attributeName) const;
    GLint getUniformLocation(const std::string& uniformName) const;
};

#endif /* Shader_hpp */
