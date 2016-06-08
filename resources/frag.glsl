#version 410

struct Light
{
    vec4 color;
    vec4 vector;
    vec4 attenuation;
};

layout (std140) uniform lightsBlock
{
    Light lights[8];
};

layout (std140) uniform matricesBlock
{
    mat4 viewProj;
};

layout(location = 1) in vec3 v_normal;
layout(location = 3) in vec3 v_tangent;
layout(location = 0) in vec2 v_texcoord;
layout(location = 2) in vec3 v_worldPosition;

layout(location = 0) out vec4 outColor;

uniform sampler2D u_sampler0;
uniform sampler2D u_sampler1;
uniform vec3 u_camPosition;

void main()
{
    outColor = vec4 (1.0, 0.0, 1.0, 1.0);
}
