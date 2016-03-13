//
//  Shader.cpp
//  HelloGL
//
//  Created by André Sá de Mello on 3/10/16.
//  Copyright © 2016 André Sá de Mello. All rights reserved.
//

#include "Shader.hpp"
#include "util.hpp"

#include <GL/glew.h>

#include <cstdio>

bool Shader::loadFromFile(const std::string& vertexShaderFilename, const std::string &fragmentShaderFilename)
{
    
    char *vsStr = util::createCString(util::loadFromFile(vertexShaderFilename));
    char *fsStr = util::createCString(util::loadFromFile(fragmentShaderFilename));
    
    char buffer[512];
    
    // Create and compile the vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsStr, NULL);
    glCompileShader(vertexShader);
    
    glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
    fprintf(stderr, "%s", buffer);
    
    // Create and compile the fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fsStr, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
    fprintf(stderr, "%s", buffer);
    
    delete vsStr;
    delete fsStr;
    
    // Link the vertex and fragment shader into a shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    
    return true;
}

void Shader::bind()
{
    glUseProgram(shaderProgram);
}

GLuint Shader::getNativeHandle()
{
    return shaderProgram;
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
}