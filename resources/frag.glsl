#version 330

in vec2 v_texcoord;
out vec4 outColor;

uniform sampler2D u_sampler;

void main()
{
    outColor = texture(u_sampler, v_texcoord.st);
}
