#version 330

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texcoord;

layout(location = 0) out vec2 v_texcoord;

layout(binding = 0) uniform mat4 u_Model;
layout(binding = 1) uniform mat4 u_ViewProj;

void main()
{
    gl_Position = u_ViewProj * u_Model * vec4(a_position, 1.0);
    v_texcoord = a_texcoord;
}
