//
//  Mesh.cpp
//  HelloGL2
//
//  Created by André Sá de Mello on 3/10/16.
//  Copyright © 2016 André Sá de Mello. All rights reserved.
//

#include "ResourcePath.hpp"
#include "Mesh.hpp"
#include "util.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

//static constexpr float TAU = static_cast<float>(2.0 * glm::pi<double>());

Mesh::Mesh(std::initializer_list<GLfloat> verts) : vertices(verts)
{
    position = glm::vec3(0, 0, 0);
    scaleFactors = glm::vec3(1, 1, 1);
    theta = phi = 0.0f;
}

void Mesh::init(const std::string& vertexShader, const std::string& fragmentShader)
{
    // Create Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    
    // Create and use a vertex/fragment shader program
    shader.loadFromFile(resourcePath() + vertexShader, resourcePath() + fragmentShader);
    shader.bind();
    
    GLuint shaderProgram = shader.getNativeHandle(); // To use with the OpenGL API
    
    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Set the initial triangle color
    uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
    glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
    
    uniTrans = glGetUniformLocation(shaderProgram, "trans");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(getTransformation()));
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::scale(float xfactor, float yfactor, float zfactor)
{
    scaleFactors *= glm::vec3(xfactor, yfactor, zfactor);
}

void Mesh::scale(float factor)
{
    scaleFactors *= glm::vec3(factor, factor, factor);
}

void Mesh::scale(glm::vec3 factors)
{
    scaleFactors *= factors;
}

void Mesh::rotate(float theta, float phi)
{
    this->theta += theta;
    this->phi += phi;
}

void Mesh::rotateZ(float theta)
{
    this->theta += theta;
}

void Mesh::rotateY(float phi)
{
    this->phi += phi;
}

void Mesh::translate(float x, float y, float z)
{
    position += glm::vec3(x, y, z);;
}

void Mesh::translate(glm::vec3 delta)
{
    position += delta;
}

glm::mat4 Mesh::getTransformation()
{
    glm::mat4 trans;
    trans = glm::translate(trans, position);
    trans = glm::rotate(trans, theta, glm::vec3(0, 0, 1));
    trans = glm::rotate(trans, phi, glm::vec3(0, 1, 0));
    trans = glm::scale(trans, scaleFactors);
    return trans;
}

void Mesh::draw(double time)
{
    // Update the triangle color
    glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
    
    // Update the transformation matrix
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(getTransformation()));
    
    // Draw a triangle from the 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 3);
}