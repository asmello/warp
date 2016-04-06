#version 410

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texcoord;

layout(location = 0) out vec2 v_texcoord;

uniform mat4 u_ViewProj;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_ViewProj * u_Model * vec4(a_position, 1.0);
    v_texcoord = a_texcoord;
}
