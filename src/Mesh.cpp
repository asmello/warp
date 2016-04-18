#include "Mesh.hpp"
#include "Transform.hpp"

using namespace warp;

//static constexpr float TAU = static_cast<float>(2.0 * glm::pi<double>());

Mesh::~Mesh()
{
    unload();
}

void Mesh::unload()
{
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::load()
{
    // Create Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    
    
    // Create an element array
    glGenBuffers(1, &ebo);
    
    // Set the data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), elements.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    
    // Specify the layout of the position data
    GLint posAttrib = 0;
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), 0);
    
    // Specify the layout of the normal data
    GLint normAttrib = 1;
    glEnableVertexAttribArray(normAttrib);
    glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat),
                          reinterpret_cast<GLvoid*>(3*sizeof(GLfloat)));
    
    // Specify the layout of the texture coordinate data
    GLint texCoordAttrib = 2;
    glEnableVertexAttribArray(texCoordAttrib);
    glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat),
                          reinterpret_cast<GLvoid*>(6*sizeof(GLfloat)));
    
    // Unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::setVertices(std::initializer_list<GLfloat> vertices_)
{
    vertices = vertices_;
}

void Mesh::setElements(std::initializer_list<GLuint> elements_)
{
    elements = elements_;
}