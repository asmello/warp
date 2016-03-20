#include "Mesh.hpp"
#include "Transform.hpp"

using namespace warp;

//static constexpr float TAU = static_cast<float>(2.0 * glm::pi<double>());

Mesh::Mesh() : eboEnabled(false), initialized(false) { }

Mesh::Mesh(std::initializer_list<GLfloat> verts) : eboEnabled(false), initialized(false), vertices(verts) { }

Mesh::~Mesh()
{
    if (initialized)
    {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteVertexArrays(1, &vao);
    }
}

void Mesh::setVertices(std::initializer_list<GLfloat> vertices)
{
    this->vertices = vertices;
}

void Mesh::setElementBuffer(std::initializer_list<GLuint> buffer)
{
    elements = buffer;
    eboEnabled = true;
}

void Mesh::init(const std::shared_ptr<const warp::Shader> shader)
{
    if (initialized) return;
    
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
        
        // Set the data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(GLuint), elements.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    // Specify the layout of the vertex data
    GLint posAttrib = shader->getAttribLocation("a_position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), 0);
    
    // Specify the layout of the texture coordinate data
    GLint texCoordAttrib = shader->getAttribLocation("a_texcoord");
    glEnableVertexAttribArray(texCoordAttrib);
    glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat),
                          reinterpret_cast<GLvoid*>(3*sizeof(GLfloat)));
    
    // Unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    initialized = true;
}

void Mesh::bind()
{
    glBindVertexArray(vao);
    if (eboEnabled) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void Mesh::draw()
{
    // Draw a mesh from the vertices
    if (eboEnabled) {
        glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/3);
    }
}