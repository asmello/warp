#include "Mesh.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

//static constexpr float TAU = static_cast<float>(2.0 * glm::pi<double>());

Mesh::Mesh()
: eboEnabled(false), position(glm::vec3(0, 0, 0)), scaleFactors(glm::vec3(1, 1, 1))  { }

Mesh::Mesh(std::initializer_list<GLfloat> verts)
: eboEnabled(false), vertices(verts), position(glm::vec3(0, 0, 0)),
scaleFactors(glm::vec3(1, 1, 1)) { }

Mesh::~Mesh()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
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
    GLint posAttrib = shader.getAttribLocation("a_position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), 0);
    
    // Specify the layout of the normal data
    GLint normAttrib = shader.getAttribLocation("a_normal");
    glEnableVertexAttribArray(normAttrib);
    glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat),
                          reinterpret_cast<GLvoid*>(3*sizeof(GLfloat)));
    
    // Specify the layout of the texture coordinate data
    GLint texCoordAttrib = shader.getAttribLocation("a_texcoord");
    glEnableVertexAttribArray(texCoordAttrib);
    glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float),
                          reinterpret_cast<GLvoid*>(6*sizeof(GLfloat)));
    
    // Unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Set the initial model matrix
    uniTrans = shader.getUniformLocation("u_Model");
    glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(getTransformation()));
    
    // Set the initial view matrix
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
    uniView = shader.getUniformLocation("u_View");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
    
    // Set the initial projection matrix
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.0f, 1.0f, 10.0f);
    uniProj = shader.getUniformLocation("u_Proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
    
    uniSampler = shader.getUniformLocation("u_sampler");
    glUniform1i(uniSampler, 0);
}

void Mesh::reshape(int width, int height)
{
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), static_cast<float>(width)/static_cast<float>(height), 1.0f, 10.0f);
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
}

void Mesh::draw(double time)
{
    
    glBindVertexArray(vao);
    
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

void Mesh::rotate(float angle, glm::vec3 axis)
{
    rotation = glm::rotate(rotation, angle, axis);
}

void Mesh::rotate(float angle, float x, float y, float z)
{
    rotation = glm::rotate(rotation, angle, glm::vec3(x, y, z));
}

void Mesh::rotateX(float angle)
{
    rotation = glm::rotate(rotation, angle, glm::vec3(1, 0, 0));
}

void Mesh::rotateY(float angle)
{
    rotation = glm::rotate(rotation, angle, glm::vec3(0, 1, 0));
}

void Mesh::rotateZ(float angle)
{
    rotation = glm::rotate(rotation, angle, glm::vec3(0, 0, 1));
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
    trans *= rotation;
    trans = glm::scale(trans, scaleFactors);
    return trans;
}
