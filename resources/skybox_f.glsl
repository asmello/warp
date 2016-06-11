#version 410

layout (std140) uniform cameraBlock
{
    mat4 u_View;
    mat4 u_Proj;
    vec3 u_camPosition;
};

layout(location = 0) in vec3 v_texcoord;

layout(location = 0) out vec4 outColor;

uniform samplerCube u_sampler0;

void main()
{
	outColor = texture(u_sampler0, v_texcoord);
}
