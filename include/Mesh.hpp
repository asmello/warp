#ifndef Mesh_h
#define Mesh_h

#include "Object.hpp"

#include <GL/glew.h>

#include <vector>
#include <memory>
#include <initializer_list>

namespace warp
{
    class Mesh : public Object<Mesh>
    {
        friend class MeshManager;
        friend class MeshRenderer;
        friend class SceneManager;
        
    public:
        ~Mesh();
        void setVertices(std::initializer_list<GLfloat> vertices);
        void setElements(std::initializer_list<GLuint> elements);
        void load();
        void unload();
        
    private:
        std::vector<std::shared_ptr<Mesh>> meshes;
        
        GLuint vao, vbo, ebo;
        std::vector<GLfloat> vertices, normals;
        std::vector<GLuint> elements;
    };
}

#endif /* Mesh_h */

