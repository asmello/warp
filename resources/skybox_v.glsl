#version 410

layout (std140) uniform cameraBlock
{
    mat4 u_View;
    mat4 u_Proj;
    vec3 u_camPosition;
};

layout(location = 0) in vec3 a_position;

layout(location = 0) out vec3 v_texcoord;

uniform mat4 u_Model;

void main()
{
    mat4 _        = u_Model;
    vec4 position = u_Proj * mat4(mat3(u_View)) * vec4(a_position, 1.0);
    gl_Position   = position.xyww;
	v_texcoord    = a_position;
}
