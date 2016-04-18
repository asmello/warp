#ifndef Transform_hpp
#define Transform_hpp

#include "Component.hpp"

#include <vector>
#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <assimp/types.h>

namespace warp
{
    class Transform : public Component
    {
    private:
        glm::vec3 position, scaleFactors;
        glm::quat rotation;
        std::vector<std::shared_ptr<Transform>> children;
        std::shared_ptr<Transform> parent;
        
        template <typename TReal>
        static inline void Decompose (const aiMatrix4x4t<TReal>& mat,
                               aiVector3t<TReal>& scaling,
                               aiQuaterniont<TReal>& rotation,
                               aiVector3t<TReal>& position)
        {
            const aiMatrix4x4t<TReal>& _this = mat;
            
            // extract translation
            position.x = _this[0][3];
            position.y = _this[1][3];
            position.z = _this[2][3];
            
            // extract the rows of the matrix
            aiVector3t<TReal> vRows[3] = {
                aiVector3t<TReal>(_this[0][0],_this[1][0],_this[2][0]),
                aiVector3t<TReal>(_this[0][1],_this[1][1],_this[2][1]),
                aiVector3t<TReal>(_this[0][2],_this[1][2],_this[2][2])
            };
            
            // extract the scaling factors
            scaling.x = vRows[0].Length();
            scaling.y = vRows[1].Length();
            scaling.z = vRows[2].Length();
            
            // and the sign of the scaling
            if (_this.Determinant() < 0) {
                scaling.x = -scaling.x;
                scaling.y = -scaling.y;
                scaling.z = -scaling.z;
            }
            
            // and remove all scaling from the matrix
            if(scaling.x)
            {
                vRows[0] /= scaling.x;
            }
            if(scaling.y)
            {
                vRows[1] /= scaling.y;
            }
            if(scaling.z)
            {
                vRows[2] /= scaling.z;
            }
            
            // build a 3x3 rotation matrix
            aiMatrix3x3t<TReal> m(vRows[0].x,vRows[1].x,vRows[2].x,
                                  vRows[0].y,vRows[1].y,vRows[2].y,
                                  vRows[0].z,vRows[1].z,vRows[2].z);
            
            // and generate the rotation quaternion from it
            rotation = aiQuaterniont<TReal>(m);
        }
        
    public:
        Transform();
        Transform(Object<GameObject>::ID gameObject);
        Transform(const aiMatrix4x4& gameObject);
        
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
        void lookAt(glm::vec3 point, glm::vec3 up);
        void setPosition(glm::vec3 position);
        void setRotation(glm::quat q);
        void setParent(std::shared_ptr<Transform> parent);
        glm::mat4 getTransformation();
    };
}

#endif /* Transform_hpp */
