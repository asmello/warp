#ifndef Mesh_h
#define Mesh_h

#include "Shader.hpp"
#include "Transform.hpp"

#include <GL/glew.h>

#include <vector>
#include <memory>
#include <initializer_list>

namespace warp {
    class Mesh {
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
        void init(const std::shared_ptr<const warp::Shader> shader);
        void bind();
        void draw();
    };
}

#endif /* Mesh_h */

