//
//  Mesh.hpp
//  HelloGL2
//
//  Created by André Sá de Mello on 3/10/16.
//  Copyright © 2016 André Sá de Mello. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h

#include "Object.hpp"

#include <GL/glew.h>

#include <vector>
#include <initializer_list>

class Mesh : Object {
private:
    GLuint vao, vbo;
    std::vector<GLfloat> vertices;
    
public:
    Mesh(std::initializer_list<GLfloat> vertices);
    ~Mesh();
    void bind();
};


#endif /* Mesh_h */
