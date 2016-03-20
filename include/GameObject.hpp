//
//  GameObject.hpp
//  Warp
//
//  Created by André Sá de Mello on 3/18/16.
//
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"

#include <memory>

namespace warp {
    class GameObject {
    private:
        std::shared_ptr<Transform> transform;
        std::shared_ptr<Texture> texture;
        std::shared_ptr<Mesh> mesh;
        
    public:
        GameObject(const std::shared_ptr<Texture>,
                   const std::shared_ptr<Mesh>,
                   const std::shared_ptr<Transform>);
        GameObject(const std::shared_ptr<Texture>,
                   const std::shared_ptr<Mesh>);
        void draw();
        void init(const std::shared_ptr<const Shader> shader);
        std::shared_ptr<Transform> getTransform();
    };
}

#endif /* GameObject_hpp */
