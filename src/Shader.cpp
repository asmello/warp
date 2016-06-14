#include "Shader.hpp"
#include "ShaderManager.hpp"

#include "util.hpp"

#include <GL/glew.h>

#include <cstdio>

using namespace warp;

template<> ResourceManager<Shader> * Object<Shader>::manager = ShaderManager::getInstance();

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
        fprintf(stderr, "SHADER_CC_ERROR: %s\n%s", typeString(type), infoLog);
        delete[] infoLog;
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
        delete[] infoLog;
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
        delete[] infoLog;
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
    if (loc < 0)
    {
        fprintf(stderr, "WARN: invalid shader attribute %s\n", attributeName.c_str());
    }
    return loc;
}

GLint Shader::getUniformLocation(const std::string &uniformName) const
{
    GLint loc = glGetUniformLocation(shaderProgram, uniformName.c_str());
    if (loc < 0)
    {
        //fprintf(stderr, "WARN: invalid shader uniform %s\n", uniformName.c_str());
    }
    return loc;
}

void Shader::setUniformBlockBinding(const std::string& uniformBlockName, GLint loc)
{
    if (loc < 0)
    {
        fprintf(stderr, "WARN: invalid location. Uniform block %s not bound.\n", uniformBlockName.c_str());
    }
    GLuint idx = glGetUniformBlockIndex(shaderProgram, uniformBlockName.c_str());
    if (idx == GL_INVALID_INDEX)
    { 
        fprintf(stderr, "WARN: uniform block %s not found. Not bound.\n", uniformBlockName.c_str());
    }
    glUniformBlockBinding(shaderProgram, idx, loc);
}

std::vector<std::string> Shader::getUniformBlockNames() const
{
    GLint numBlocks;
    glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORM_BLOCKS, &numBlocks);
    std::vector<std::string> blockNames;
    blockNames.reserve(numBlocks);
    for(int blockIx = 0; blockIx < numBlocks; ++blockIx)
    {
        GLint nameLen;
        glGetActiveUniformBlockiv(shaderProgram, blockIx, GL_UNIFORM_BLOCK_NAME_LENGTH, &nameLen);
        
        std::vector<GLchar> name;
        name.resize(nameLen);
        glGetActiveUniformBlockName(shaderProgram, blockIx, nameLen, NULL, &name[0]);
        
        blockNames.push_back(std::string());
        blockNames.back().assign(name.begin(), name.end() - 1); //Remove the null terminator.
    }
    return blockNames;
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}

const char * Shader::typeString(GLenum type)
{
    switch (type)
    {
        case GL_FRAGMENT_SHADER:
            return "FRAGMENT SHADER";
        case GL_VERTEX_SHADER:
            return "VERTEX SHADER";
        default:
            return "UNKNOWN TYPE";
    }
}
