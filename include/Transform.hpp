//
//  Transform.hpp
//  Warp
//
//  Created by André Sá de Mello on 3/19/16.
//
//

#ifndef Transform_hpp
#define Transform_hpp

#include "Shader.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace warp {
    class Transform {
    private:
        GLint uniTrans;
        glm::vec3 position, scaleFactors;
        glm::mat4 rotation;
        bool initialized;
        
    public:
        Transform();
        void init(const std::shared_ptr<const warp::Shader> shader);
        void bind();
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
}

#endif /* Transform_hpp */