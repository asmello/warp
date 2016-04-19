#version 410

layout(location = 1) in vec3 v_normal;
layout(location = 3) in vec3 v_tangent;
layout(location = 0) in vec2 v_texcoord;
layout(location = 2) in vec3 v_worldPosition;

layout(location = 0) out vec4 outColor;

uniform sampler2D u_sampler0;
uniform sampler2D u_sampler1;
uniform vec3 u_camPosition;


struct DirectionalLight {
	vec3 color;
	float intensity;
	vec3 direction;
};

vec3 CalcBumpedNormal (){
    vec3 Normal = normalize(v_normal);
    vec3 Tangent = normalize(v_tangent);
    Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
    vec3 Bitangent = cross(Tangent, Normal);
    vec3 BumpMapNormal = vec3 (texture(u_sampler1, v_texcoord).x, 1-texture(u_sampler1, v_texcoord).y, texture(u_sampler1, v_texcoord).z);
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
    vec3 NewNormal;
    mat3 TBN = mat3(Tangent, Bitangent, Normal);
    NewNormal = TBN * BumpMapNormal;
    NewNormal = normalize(NewNormal);
    return NewNormal;
}


void main()
{

	DirectionalLight sun = DirectionalLight (
		vec3 (1.0, 1.0, 0.93),
		1.0,
		vec3 (-0.15, -0.1, -0.9)
	);

	//Lights
	vec4 ambientLight = vec4 (0.1, 0.06, 0.15, 1.0) * 1;
	vec3 sunNormalized = normalize (sun.direction);
	vec4 specularColor = vec4 (1.0, 1.0, 1.0, 1.0);

	//UsefullVectors
	vec3 normalNormalized = normalize (v_normal);
	vec3 tangentNormalized = normalize (v_tangent);
	vec3 bitangentNormalized = cross (tangentNormalized, normalNormalized);
	vec3 viewDirection = normalize (u_camPosition - v_worldPosition);
	vec3 HalfDirection = normalize ((sunNormalized - viewDirection)*0.5);

	//FindPerturbedNormals
	//mat3 tangentToWorld = mat3 (tangentNormalized, bitangentNormalized, normalNormalized);
	vec3 perturbedNormals = CalcBumpedNormal (); //transpose (tangentToWorld) * (2 * texture (u_sampler1, v_texcoord.st).xyz - 1);

	//Calculate lightning
	vec4 ambient  = ambientLight * texture(u_sampler0, v_texcoord.st);
	vec4 difuse   = max (0.0, dot (-sunNormalized, perturbedNormals)) * texture(u_sampler0, v_texcoord.st);
	vec4 specular = 1.0 * pow (max (0.0, dot (-HalfDirection, perturbedNormals)) , 50.0) * specularColor * texture(u_sampler0, v_texcoord.st) * texture(u_sampler0, v_texcoord.st).w;
	vec4 rim      = 0.3 * pow(- max (0.0, dot (viewDirection, perturbedNormals)) + 1.0, 1.0) * ambientLight;

    outColor = (difuse + specular + ambient + rim);// * 0.01 + vec4 (perturbedNormals, 1.0);

}
