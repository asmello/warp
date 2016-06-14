#version 410

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_texcoord;

layout(location = 0) out vec2 v_texcoord;

void main()
{
    gl_Position   = vec4(a_position.x, a_position.y, 0.0f, 1.0f);
	v_texcoord    = a_texcoord;
}
