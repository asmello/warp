//
//  Mesh.hpp
//  HelloGL2
//
//  Created by André Sá de Mello on 3/10/16.
//  Copyright © 2016 André Sá de Mello. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <vector>
#include <initializer_list>

class Mesh {
private:
    GLuint vao, vbo;
    std::vector<GLfloat> vertices;
    glm::mat4 trans;
    
public:
    Mesh(std::initializer_list<GLfloat> vertices);
    ~Mesh();
    void bind();
    void scale(float xfactor, float yfactor, float zfactor);
    void scale(glm::vec3 factors);
    void scale(float factor);
    void rotate(float angle, glm::vec3 axis);
    void translate(float x, float y, float z);
    void translate(glm::vec3 delta);
    glm::mat4& getTransformation();
};


#endif /* Mesh_h */
