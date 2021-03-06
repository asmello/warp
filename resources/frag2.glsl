#version 410

struct Light
{
    vec4 color;
    vec4 vector;
    vec4 attenuation;
};

layout (std140) uniform lightsBlock
{
    Light lights[8];
};

layout (std140) uniform cameraBlock
{
    mat4 u_View;
    mat4 u_Proj;
    vec3 u_camPosition;
};

layout(location = 1) in vec3 v_normal;
layout(location = 3) in vec3 v_tangent;
layout(location = 0) in vec2 v_texcoord;
layout(location = 2) in vec3 v_worldPosition;

layout(location = 0) out vec4 outColor;

uniform sampler2D u_sampler0;
uniform sampler2D u_sampler1;

float LightAttenuation (Light curLight, vec3 fragPosition){

	float lightDistance = length (fragPosition -curLight.vector.xyz);

	float pointAttenuation = 1.0 / (curLight.attenuation.x + curLight.attenuation.y * lightDistance + curLight.attenuation.z * lightDistance * lightDistance);
	float directionalAttenuation = 1.0;
	float spotAttenuation = 1.0;

	return max (0.0, mix (pointAttenuation, directionalAttenuation, curLight.vector.w));

}

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

vec4 ShadePhong (Light curLight, vec3 fragPos, vec3 normal, vec3 viewDirection, vec4 textureColor, float specularity, float roughness, float metalic){

	vec3 lightDir = mix (normalize (curLight.vector.xyz - fragPos), -curLight.vector.xyz, curLight.vector.w);
	vec3 lightReflect = reflect (lightDir, normal);
	float atten = LightAttenuation (curLight, fragPos);

	vec4 difuse = max (0.0, dot (lightDir, normal)) * textureColor * curLight.color * atten;
	vec4 specular = 1.0 * pow (max (0.0, dot (viewDirection, lightReflect)) , roughness) * mix (curLight.color, textureColor, metalic) * textureColor.w;

	vec4 finalColor = min (difuse + specularity * specular * 0.0, 1.0); //vec4 (1.0, 1.0, 1.0, 1.0) * dot (viewDirection, normal)
	return finalColor;

}

void main()
{
	//Lights
	vec4 ambientLight = vec4 (0.01, 0.003, 0.001, 1.0) * 1;
	vec3 sunNormalized = vec3 (0.0, 1.0, 0.0);
	vec4 specularColor = vec4 (1.0, 1.0, 1.0, 1.0);

	//UsefulVectors
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
	vec4 rim      = 0.3 * pow(- max (0.0, dot (viewDirection, perturbedNormals)) + 1.0, 1.0) * ambientLight;

	Light testLight1 = Light (vec4 (1.0, 0.054, 0.017, 1.0) * 200.0, vec4 (-0.0, 80.0, 0.0, 0.0),  vec4 (0.0, 1.0, 0.1, 1.0));

	Light testLight2 = Light (vec4 (1.0, 0.211, 0.008, 1.0) * 30.0, vec4 (40.0, 14.0, 60.0, 0.0), vec4 (0.0, 1.0, 0.1, 1.0));
	Light testLight3 = Light (vec4 (1.0, 0.211, 0.008, 1.0) * 30.0, vec4 (-40.0, 14.0, 60.0, 0.0), vec4 (0.0, 1.0, 0.1, 1.0));
	Light testLight4 = Light (vec4 (1.0, 0.211, 0.008, 1.0) * 30.0, vec4 (40.0, 14.0, -60.0, 0.0), vec4 (0.0, 1.0, 0.1, 1.0));
	Light testLight5 = Light (vec4 (1.0, 0.211, 0.008, 1.0) * 30.0, vec4 (-40.0, 14.0, -60.0, 0.0), vec4 (0.0, 1.0, 0.1, 1.0));

	Light testLight6 = Light (vec4 (1.0, 0.039, 0.009, 1.0) * 45.0, vec4 (50.0, -20.0, 0.0, 0.0), vec4 (0.0, 1.0, 0.1, 1.0));
	Light testLight7 = Light (vec4 (1.0, 0.039, 0.009, 1.0) * 45.0, vec4 (-50.0, -20.0, 0.0, 0.0), vec4 (0.0, 1.0, 0.1, 1.0));

	vec4 difSpec =      ShadePhong (testLight1, v_worldPosition, perturbedNormals, viewDirection, texture (u_sampler0, v_texcoord.st), 0.1, 10.0, 0.0);
	difSpec = difSpec + ShadePhong (testLight2, v_worldPosition, perturbedNormals, viewDirection, texture (u_sampler0, v_texcoord.st), 0.1, 10.0, 0.0);
	difSpec = difSpec + ShadePhong (testLight3, v_worldPosition, perturbedNormals, viewDirection, texture (u_sampler0, v_texcoord.st), 0.1, 10.0, 0.0);
	difSpec = difSpec + ShadePhong (testLight4, v_worldPosition, perturbedNormals, viewDirection, texture (u_sampler0, v_texcoord.st), 0.1, 10.0, 0.0);
	difSpec = difSpec + ShadePhong (testLight5, v_worldPosition, perturbedNormals, viewDirection, texture (u_sampler0, v_texcoord.st), 0.1, 10.0, 0.0);
	difSpec = difSpec + ShadePhong (testLight6, v_worldPosition, perturbedNormals, viewDirection, texture (u_sampler0, v_texcoord.st), 0.1, 10.0, 0.0);
	difSpec = difSpec + ShadePhong (testLight7, v_worldPosition, perturbedNormals, viewDirection, texture (u_sampler0, v_texcoord.st), 0.1, 10.0, 0.0);

	//vec4 difuse   = max (0.0, dot (-sunNormalized, perturbedNormals)) * texture(u_sampler0, v_texcoord.st);
	//vec4 specular = 1.0 * pow (max (0.0, dot (-HalfDirection, perturbedNormals)) , 50.0) * specularColor * texture(u_sampler0, v_texcoord.st) * texture(u_sampler0, v_texcoord.st).w;

    outColor = (difSpec + ambient + rim);// * 0.01 + vec4 (perturbedNormals, 1.0);
}
