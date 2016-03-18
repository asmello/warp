#version 330

in vec3 a_position;
in vec3 a_normal;
in vec2 a_texcoord;

out vec2 v_texcoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
    gl_Position = u_Proj * u_View * u_Model * vec4(a_position, 1.0);
    v_texcoord = a_texcoord;
}
