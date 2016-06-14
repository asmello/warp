#version 410

layout(location = 0) in vec2 v_texcoord;

layout(location = 0) out vec4 outColor;

uniform sampler2D u_sampler0;
uniform sampler2D u_sampler1;
uniform float exposure;

void main()
{
    vec3 hdrColor = texture(u_sampler0, v_texcoord).rgb;
    hdrColor += texture(u_sampler1, v_texcoord).rgb;
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
	outColor = vec4(mapped, 1.0);
}
