#version 410

layout(location = 0) in vec2 v_texcoord;

layout(location = 0) out vec4 outColor;

uniform sampler2D u_sampler0;

void main()
{
    outColor = texture(u_sampler0, v_texcoord.st);
}
