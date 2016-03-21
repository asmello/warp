#include "Shader.hpp"
using namespace warp;

#include "util.hpp"

#include <GL/glew.h>

#include <cstdio>

void Shader::loadFromFile(const std::string& vertexShaderFilename, const std::string &fragmentShaderFilename)
{
    
    char *vsStr = util::createCString(util::loadFromFile(vertexShaderFilename));
    char *fsStr = util::createCString(util::loadFromFile(fragmentShaderFilename));
    
    // Create and compile the vertex shader
    GLint vertexShader = compile(GL_VERTEX_SHADER, vsStr);
    
    delete vsStr;
    
    // Create and compile the fragment shader
    GLint fragmentShader = compile(GL_FRAGMENT_SHADER, fsStr);
    
    delete fsStr;
    
    // Link the vertex and fragment shader into a shader program
    link(vertexShader, fragmentShader);
    
    // These aren't necessary anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLint Shader::compile(GLenum type, char *source)
{
    // Create and compile the fragment shader
    GLint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    GLint param;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &param);
    if (param == GL_FALSE)
    {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &param);
        char *infoLog = new char[param];
        glGetShaderInfoLog(shader, param, NULL, infoLog);
        fprintf(stderr, "SHADER_CC_ERROR:\n%s", infoLog);
        delete infoLog;
    }
    
    return shader;
}

void Shader::link(GLint vertexShader, GLint fragmentShader)
{
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    
    GLint param;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &param);
    if (param == GL_FALSE)
    {
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &param);
        char *infoLog = new char[param];
        glGetProgramInfoLog(shaderProgram, param, NULL, infoLog);
        fprintf(stderr, "*** SHADER_LINKER_ERROR\n%s", infoLog);
        delete infoLog;
    }
}

void Shader::validate()
{
    glValidateProgram(shaderProgram);
    
    GLint param;
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &param);
    if (param == GL_FALSE)
    {
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &param);
        char *infoLog = new char[param];
        glGetProgramInfoLog(shaderProgram, param, NULL, infoLog);
        fprintf(stderr, "*** SHADER_PROGRAM_ERROR\n%s", infoLog);
        delete infoLog;
    }
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
    GLint loc = glGetAttribLocation(shaderProgram, attributeName.c_str());
    if (loc < 0) {
        throw std::runtime_error("invalid shader attribute");
    }
    return loc;
}

GLint Shader::getUniformLocation(const std::string &uniformName) const
{
    GLint loc = glGetUniformLocation(shaderProgram, uniformName.c_str());
    if (loc < 0) {
        throw std::runtime_error("invalid shader uniform");
    }
    return loc;
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}
