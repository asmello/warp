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

layout (std140) uniform cameraBlock
{
    mat4 u_viewProj;
    vec3 u_camPosition;
};

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec3 a_tangent;
layout(location = 3) in vec2 a_texcoord;

layout(location = 2) out vec3 v_worldPosition;
layout(location = 1) out vec3 v_normal;
layout(location = 3) out vec3 v_tangent;
layout(location = 0) out vec2 v_texcoord;

uniform mat4 u_Model;
//uniform DirectionalLight u_sun;

void main()
{
    gl_Position     =  u_viewProj * u_Model * vec4(a_position, 1.0);
    v_normal        = (u_Model * vec4(a_normal,   0.0)).xyz;
	v_worldPosition = (u_Model * vec4(a_position, 1.0)).xyz;
	v_tangent       = (u_Model * vec4(a_tangent,  0.0)).xyz;
	v_texcoord      = a_texcoord;
}
