#ifndef Mesh_h
#define Mesh_h

#include "GameObject.hpp"
#include "Transform.hpp"

#include <GL/glew.h>

#include <vector>
#include <memory>
#include <initializer_list>

namespace warp
{
    class Mesh : public GameObject
    {
    private:
        GLuint vao, vbo, ebo;
        bool eboEnabled, initialized;
        std::vector<GLfloat> vertices, normals;
        std::vector<GLuint> elements;
        
    public:
        Mesh();
        Mesh(std::initializer_list<GLfloat> vertices);
        ~Mesh();
        void setVertices(std::initializer_list<GLfloat> vertices);
        void setElementBuffer(std::initializer_list<GLuint> buffer);
        void init();
        void bind();
        void draw();
    };
}

#endif /* Mesh_h */

