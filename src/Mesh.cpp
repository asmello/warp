//
//  Mesh.cpp
//  HelloGL2
//
//  Created by André Sá de Mello on 3/10/16.
//  Copyright © 2016 André Sá de Mello. All rights reserved.
//

#include "Mesh.hpp"

#include <glm/gtc/matrix_transform.hpp>

Mesh::Mesh(std::initializer_list<GLfloat> verts) : vertices(verts)
{
    // Create Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
}

void Mesh::scale(float xfactor, float yfactor, float zfactor)
{
    trans = glm::scale(trans, glm::vec3(xfactor, yfactor, zfactor));
}

void Mesh::scale(glm::vec3 factors)
{
    trans = glm::scale(trans, factors);
}

void Mesh::scale(float factor)
{
    trans = glm::scale(trans, glm::vec3(factor, factor, factor));
}

void Mesh::rotate(float angle, glm::vec3 axis)
{
    trans = glm::rotate(trans, glm::radians(angle), axis);
}

void Mesh::translate(float x, float y, float z)
{
    trans = glm::translate(trans, glm::vec3(x, y, z));
}

void Mesh::translate(glm::vec3 delta)
{
    trans = glm::translate(trans, delta);
}

glm::mat4& Mesh::getTransformation()
{
    return trans;
}