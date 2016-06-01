#include "Light.hpp"

#include <algorithm>

#include <glm/gtc/type_ptr.hpp>

using namespace warp;

Light::Light(Light::Type type)
{
    setType(type);
}

GLfloat *Light::getData() const
{
    static GLfloat data_buffer[12];
    std::copy_n(glm::value_ptr(data), 12, data_buffer);
    return data_buffer;
}

void Light::setColor(glm::vec3 rgb)
{
    data[0][0] = rgb.r;
    data[0][1] = rgb.g;
    data[0][2] = rgb.b;
}

void Light::setVector(glm::vec3 vector)
{
    data[1][0] = vector.x;
    data[1][1] = vector.y;
    data[1][2] = vector.z;
}

void Light::setType(Light::Type type)
{
    switch (type)
    {
        case Light::Type::Directional:
            data[1][3] = 1.0f;
            break;
        case Light::Type::Point:
            data[1][3] = 0.0f;
            break;
    }
}

void Light::setAttenuation(glm::vec4 factors)
{
    data[2][0] = factors[0];
    data[2][1] = factors[1];
    data[2][2] = factors[2];
    data[2][3] = factors[3];
}
