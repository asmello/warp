#ifndef SkyboxRenderer_hpp
#define SkyboxRenderer_hpp

#include "Object.hpp"
#include "Renderer.hpp"

#include <GL/glew.h>

namespace warp {
    class Material;
    
    class SkyboxRenderer : public Renderer
    {
        
    public:
        SkyboxRenderer(Object<Material>::ID materialID);
        ~SkyboxRenderer();
        virtual void render(float time);
        
    private:
        Object<Material>::ID materialID;
        GLuint vao, vbo;
        
        void load();
        void unload();
    };
}

#endif /* SkyboxRenderer_hpp */
