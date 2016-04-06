#version 330

layout(location = 0) in vec2 v_texcoord;

layout(location = 0) out vec4 outColor;

layout(binding = 2) uniform sampler2D u_sampler;

void main()
{
    outColor = texture(u_sampler, v_texcoord.st);
}
