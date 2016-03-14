//
//  Mesh.cpp
//  HelloGL2
//
//  Created by André Sá de Mello on 3/10/16.
//  Copyright © 2016 André Sá de Mello. All rights reserved.
//

#include "Mesh.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

//static constexpr float TAU = static_cast<float>(2.0 * glm::pi<double>());

Mesh::Mesh()
: theta(0.0f), phi(0.0f), eboEnabled(false), position(glm::vec3(0, 0, 0)), scaleFactors(glm::vec3(1, 1, 1)) { }

Mesh::Mesh(std::initializer_list<GLfloat> verts)
: theta(0.0f), phi(0.0f), eboEnabled(false), vertices(verts), position(glm::vec3(0, 0, 0)),
scaleFactors(glm::vec3(1, 1, 1)) { }

Mesh::~Mesh()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::setVertices(std::initializer_list<GLfloat> verts)
{
    vertices = verts;
}

void Mesh::setElementBuffer(std::initializer_list<GLuint> buffer)
{
    elements = buffer;
    eboEnabled = true;
}

void Mesh::init(const Shader& shader)
{
    // Create Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    
    if (eboEnabled)
    {
        // Create an element array
        glGenBuffers(1, &ebo);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), elements.data(), GL_STATIC_DRAW);
    }
    
    // Specify the layout of the vertex data
    GLint posAttrib = shader.getAttribLocation("position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Set the initial triangle color
    uniColor = shader.getUniformLocation("u_Color");
    glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
    
    // Set the initial transformation matrix
    uniTrans = shader.getUniformLocation("u_Model");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(getTransformation()));
}

void Mesh::draw(double time)
{
    glBindVertexArray(vao);
    
    // Update the mesh color
    glUniform3f(uniColor,
                (sin(time * 4.0f) + 1.0f) / 2.0f,
                (sin(time * 4.1f + 0.33f) + 1.0f) / 2.0f,
                (sin(time * 3.7f + 0.80f) + 1.0f) / 2.0f);
    
    // Update the transformation matrix
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(getTransformation()));
    
    // Draw a mesh from the vertices
    if (eboEnabled) {
        glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/3);
    }
    
    glBindVertexArray(0);
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
    position += glm::vec3(x, y, z);
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
