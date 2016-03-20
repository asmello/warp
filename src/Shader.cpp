#include "Shader.hpp"
using namespace warp;

#include "util.hpp"

#include <GL/glew.h>

#include <cstdio>

bool Shader::loadFromFile(const std::string& vertexShaderFilename, const std::string &fragmentShaderFilename)
{
    
    char *vsStr = util::createCString(util::loadFromFile(vertexShaderFilename));
    char *fsStr = util::createCString(util::loadFromFile(fragmentShaderFilename));
    
    char buffer[512];
    
    // Create and compile the vertex shader
    GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsStr, NULL);
    glCompileShader(vertexShader);
    
    glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
    fprintf(stderr, "%s", buffer);
    
    delete vsStr;
    
    // Create and compile the fragment shader
    GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fsStr, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
    fprintf(stderr, "%s", buffer);
    
    delete fsStr;
    
    // Link the vertex and fragment shader into a shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return true;
}

void Shader::bind()
{
    glUseProgram(shaderProgram);
}

GLuint Shader::getNativeHandle() const
{
    return shaderProgram;
}

GLint Shader::getAttribLocation(const std::string &attributeName) const
{
    return glGetAttribLocation(shaderProgram, attributeName.c_str());
}

GLint Shader::getUniformLocation(const std::string &uniformName) const
{
    return glGetUniformLocation(shaderProgram, uniformName.c_str());
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}
