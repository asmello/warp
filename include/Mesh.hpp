#ifndef Mesh_h
#define Mesh_h

#include "Shader.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>
#include <initializer_list>

class Mesh {
private:
    GLint uniTrans, uniColor;
    GLuint vao, vbo, ebo;
    bool eboEnabled;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> elements;
    glm::vec3 position, scaleFactors;
    glm::mat4 rotation;
    
public:
    Mesh();
    Mesh(std::initializer_list<GLfloat> vertices);
    ~Mesh();
    void setVertices(std::initializer_list<GLfloat> verts);
    void setElementBuffer(std::initializer_list<GLuint> buffer);
    void init(const Shader& shader);
    void draw(double time);
    void scale(float xfactor, float yfactor, float zfactor);
    void scale(glm::vec3 factors);
    void scale(float factor);
    void rotate(float angle, glm::vec3 axis);
    void rotate(float angle, float x, float y, float z);
    void rotateX(float radians);
    void rotateY(float radians);
    void rotateZ(float radians);
    void translate(float x, float y, float z);
    void translate(glm::vec3 delta);
    glm::mat4 getTransformation();
};


#endif /* Mesh_h */

