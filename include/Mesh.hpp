#ifndef Mesh_h
#define Mesh_h

#include "Object.hpp"

#include <GL/glew.h>

#include <vector>
#include <memory>
#include <initializer_list>

namespace warp
{
    class Material;
    
    class Mesh : public Object<Mesh>
    {
        friend class MeshManager;
        friend class MeshRenderer;
        
    public:
        struct MeshEntry {
            ~MeshEntry();
            
            void load();
            void unload();
            
            GLuint vao, vbo, ebo;
            std::vector<GLfloat> vertices, normals;
            std::vector<GLuint> elements;
            Object<Material>::ID materialID;
        };
        
        void addEntry(std::shared_ptr<MeshEntry> entry);
        
    private:
        std::vector<std::shared_ptr<MeshEntry>> meshes;
    };
}

#endif /* Mesh_h */

