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
layout(location = 1) out vec4 outBright;

uniform sampler2D u_sampler0;
uniform sampler2D u_sampler1;
uniform sampler2D u_sampler2;
uniform samplerCube u_sampler3;
uniform samplerCube u_sampler4;
uniform sampler2D u_sampler5;

uniform float u_time;

const float PI = 3.141592653589793238462643383;

float LightAttenuation (Light curLight, vec3 fragPosition){

	float lightDistance = length (fragPosition -curLight.vector.xyz);

	float pointAttenuation = 1.0 / (curLight.attenuation.x + curLight.attenuation.y * lightDistance + curLight.attenuation.z * lightDistance * lightDistance);
	float directionalAttenuation = 1.0;
	float spotAttenuation = 1.0;

	return max (0.0, mix (pointAttenuation, directionalAttenuation, curLight.vector.w));

}

highp float rand(vec2 co){

    highp float a = 12.9898;
    highp float b = 78.233;
    highp float c = 43758.5453;
    highp float dt= dot(co.xy ,vec2(a,b));
    highp float sn= mod(dt,3.14);
    return fract (sin(sn) * c);

}

vec3 CalcBumpedNormal (vec3 normal, vec3 tangent, vec4 normalMap){

    vec3 Normal = normalize(normal);
    vec3 Tangent = normalize(tangent);
    Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);
    vec3 Bitangent = cross(Tangent, Normal);
    vec3 BumpMapNormal = vec3 (normalMap.x, 1-normalMap.y, normalMap.z);
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
    vec3 NewNormal;
    mat3 TBN = mat3(Tangent, Bitangent, Normal);
    NewNormal = TBN * BumpMapNormal;
    NewNormal = normalize(NewNormal);
    return NewNormal;

}

float GGXDistributionFunction (float roughness, vec3 halfDirection, vec3 normalDirection){

	float normalOhalf = dot (normalDirection, halfDirection);
	float normalOhalf2 = normalOhalf * normalOhalf;
	float roughness2 = roughness * roughness;
	float denominator = normalOhalf2 * (roughness2 + (1.0 - normalOhalf2)/normalOhalf2 );

	return max (0.0, sign (normalOhalf)) * roughness2 / (PI * denominator * denominator);


}

float GGXPartialGeometryFunction (float roughness, vec3 inputDirection, vec3 normal, vec3 halfDirection){

    float IoH2 = max (0.0, dot(inputDirection, halfDirection));
    float chi = max (0.0, sign ( IoH2 / max (0.0, dot(inputDirection, normal)) ));
    IoH2 = IoH2 * IoH2;
    float tan2 = ( 1 - IoH2 ) / IoH2;
    return (chi * 2) / ( 1 + sqrt( 1 + roughness * roughness * tan2 ) );

}

vec4 FresnelFunction (vec3 viewDirection, vec3 halfDirection, vec4 albedoColor, float metalicness, float IOR, vec4 lightColor){

	float F0 = abs ((1.0 - IOR) / (1.0 + IOR));
	F0 = F0*F0;
	vec4 F4 = mix (vec4 (F0, F0, F0, F0) , albedoColor, metalicness);
	vec4 ones = vec4 (1.0, 1.0, 1.0, 1.0);
	return F4 + (ones - F4) * pow (1.0 - dot (viewDirection, halfDirection), 5.0);
	//return ones * dot (viewDirection, halfDirection);

}

vec4 ShadeCookTorr (Light curLight, vec3 fragPos, vec3 normal, vec3 viewDirection, vec4 albedo, float specularity, float roughness, float metalic){
	
	vec3 lightDir = mix (normalize (curLight.vector.xyz - fragPos), - normalize (curLight.vector.xyz), curLight.vector.w);
	float atten = LightAttenuation (curLight, fragPos);
	vec3 halfDirection = normalize (lightDir + viewDirection);
	
	vec4 lambert = albedo/PI * atten * curLight.color * max (0.0, dot (lightDir, normal));

	float GGXDF = GGXDistributionFunction (roughness, halfDirection, normal);
	float GGXGF = GGXPartialGeometryFunction (roughness, lightDir, normal, halfDirection) *  GGXPartialGeometryFunction (roughness, viewDirection, normal, halfDirection);
	vec4 FRNF = FresnelFunction (viewDirection, halfDirection, albedo, metalic, 2.4, curLight.color);
	float denominator = 1.0/ (4* max (0.0, dot (viewDirection, normal) * max(0.0, dot (halfDirection, normal))) + 0.05);
	vec4 cookTorr = (GGXDF * GGXGF * FRNF) * denominator * (atten * curLight.color) * max (0.0, dot (lightDir, normal));
	
	return lambert * roughness + cookTorr * (1-roughness);

}

vec4 CookTorrAmbient (samplerCube ambientLight, samplerCube convolvedAmbientLight, int sampleCount, Light curLight, vec3 fragPos, vec3 normal, vec3 tangent, vec3 viewDirection, vec4 albedo, float specularity, float roughness, float metalic){
	
	vec3 lightDir;
	vec3 halfDirection;
	vec4 lightColor;
	
	float GGXDF;
	float GGXGF;
	vec4 FRNF;
	float denominator;

	vec4 cookTorr = vec4 (0.0, 0.0, 0.0, 0.0);
	vec4 lambert;
	
	for (int i = 0 ; i < sampleCount ; i++){
		
		float r1 = rand (vec2 (float(i)/float(sampleCount), 0.5 * float(i)/float(sampleCount)));
		float r2 = rand (vec2 (0.5 * float(i)/float(sampleCount), float(i)/float(sampleCount)));
		float theta = atan (roughness * sqrt (r1)/sqrt (1-r1));
		float phi = 2.0 * PI * r2; 
		vec4 tsSampleVector = vec4 (cos (phi) * sin (theta), sin (phi) * sin (theta), cos (theta), 1.0);		


		lightDir = CalcBumpedNormal (normal, vec3 (1.0, 0.0, 0.0) ,tsSampleVector);
		halfDirection = normalize (lightDir + viewDirection);
		lightColor = texture (ambientLight, lightDir);

		GGXDF = GGXDistributionFunction (roughness, halfDirection, normal);
		GGXGF = GGXPartialGeometryFunction (roughness, lightDir, normal, halfDirection) *  GGXPartialGeometryFunction (roughness, viewDirection, normal, halfDirection);
		FRNF = FresnelFunction (viewDirection, halfDirection, albedo, metalic, 2.4, lightColor);
		denominator = 1.0/ (4* max (0.0, dot (viewDirection, normal) * max(0.0, dot (halfDirection, normal))) + 0.05);
		cookTorr = cookTorr + (GGXDF * GGXGF * FRNF) * denominator * lightColor * max (0.0, dot (lightDir, normal));
	
	}

	cookTorr = cookTorr/ float (sampleCount);

	lambert = albedo/PI * texture (convolvedAmbientLight, normal);

	return lambert * roughness + cookTorr * (1-roughness);

}

vec4 ShadePhong (Light curLight, vec3 fragPos, vec3 normal, vec3 viewDirection, vec4 textureColor, float specularity, float roughness, float metalic){

	vec3 lightDir = mix (normalize (curLight.vector.xyz - fragPos), - normalize (curLight.vector.xyz), curLight.vector.w);
	vec3 lightReflect = reflect (-lightDir, normal);
	float atten = LightAttenuation (curLight, fragPos);

	vec4 difuse = max (0.0, dot (lightDir, normal)) * textureColor * curLight.color * atten;
	vec4 specular = pow (max (0.0, dot (viewDirection, lightReflect)) , roughness) * mix (curLight.color, textureColor, metalic) * specularity * atten;

	vec4 finalColor = difuse + specular;
	return finalColor;

}


void main(){

	//Shader parameters

	float moveSpeed = 1.0;
	vec2 movingUvs = v_texcoord.st + vec2 (0.0, 1.0) * moveSpeed * u_time;
	vec4 albedo = texture (u_sampler0, movingUvs);
	float specularity = 0.0;
	float roughness = texture (u_sampler0, movingUvs).w; 
	float metalicness = texture (u_sampler5, movingUvs).x;
	float emission = 1.0;
	vec4 normalMap = texture (u_sampler1, movingUvs);
	vec4 emissionColor = texture (u_sampler2, movingUvs);
	float transparency = texture (u_sampler5, movingUvs).w;

	//Vectors
	vec3 normalNormalized = normalize (v_normal);
	vec3 tangentNormalized = normalize (v_tangent);
	vec3 viewDirection = normalize (u_camPosition - v_worldPosition);
	vec3 perturbedNormals = CalcBumpedNormal (normalNormalized, tangentNormalized, normalMap);

	//Calculate lightning
	vec4 emmit = emissionColor * emission;
	
	float lighStrength = 5.0;

	if (transparency < 0.5){
		discard;
	}


	Light sun = Light (vec4 (1.0, 1.0, 1.0, 1.0) * 1.0, vec4 ( -0.5, -1.0, 0.5, 1.0),  vec4 (0.0, 1.0, 0.1, 1.0));
	Light black = Light (vec4 (0.0, 0.0, 0.0, 0.0), vec4 ( 0.0, 0.0, 0.0, 0.0),  vec4 (1.0, 0.0, 0.0, 0.0));

	Light testLight1 = Light (vec4 (1.0, 0.054, 0.017, 1.0) * 200.0 * lighStrength, vec4 (-0.0, 80.0, 0.0, 0.0),  vec4 (0.0, 1.0, 0.1, 1.0));

	Light testLight2 = Light (vec4 (1.0, 0.211, 0.008, 1.0) * 30.0 * lighStrength, vec4 (40.0, 14.0, 60.0, 0.0), vec4 (0.0, 1.0, 0.1, 1.0));
	Light testLight3 = Light (vec4 (1.0, 0.211, 0.008, 1.0) * 30.0 * lighStrength, vec4 (-40.0, 14.0, 60.0, 0.0), vec4 (0.0, 1.0, 0.1, 1.0));
	Light testLight4 = Light (vec4 (1.0, 0.211, 0.008, 1.0) * 30.0 * lighStrength, vec4 (40.0, 14.0, -60.0, 0.0), vec4 (0.0, 1.0, 0.1, 1.0));
	Light testLight5 = Light (vec4 (1.0, 0.211, 0.008, 1.0) * 30.0 * lighStrength, vec4 (-40.0, 14.0, -60.0, 0.0), vec4 (0.0, 1.0, 0.1, 1.0));

	Light testLight6 = Light (vec4 (1.0, 0.039, 0.009, 1.0) * 45.0 * lighStrength, vec4 (50.0, -20.0, 0.0, 0.0), vec4 (0.0, 1.0, 0.1, 1.0));
	Light testLight7 = Light (vec4 (1.0, 0.039, 0.009, 1.0) * 45.0 * lighStrength, vec4 (-50.0, -20.0, 0.0, 0.0), vec4 (0.0, 1.0, 0.1, 1.0));

	vec4 difSpec =      ShadeCookTorr (testLight1, v_worldPosition, perturbedNormals, viewDirection, albedo, specularity, roughness, metalicness);
	difSpec = difSpec + ShadeCookTorr (testLight2, v_worldPosition, perturbedNormals, viewDirection, albedo, specularity, roughness, metalicness);
	difSpec = difSpec + ShadeCookTorr (testLight3, v_worldPosition, perturbedNormals, viewDirection, albedo, specularity, roughness, metalicness);
	difSpec = difSpec + ShadeCookTorr (testLight4, v_worldPosition, perturbedNormals, viewDirection, albedo, specularity, roughness, metalicness);
	difSpec = difSpec + ShadeCookTorr (testLight5, v_worldPosition, perturbedNormals, viewDirection, albedo, specularity, roughness, metalicness);
	difSpec = difSpec + ShadeCookTorr (testLight6, v_worldPosition, perturbedNormals, viewDirection, albedo, specularity, roughness, metalicness);
	difSpec = difSpec + ShadeCookTorr (testLight7, v_worldPosition, perturbedNormals, viewDirection, albedo, specularity, roughness, metalicness);
	
	//difSpec = 1.0 * CookTorrAmbient (u_sampler3, u_sampler4, 10, black, v_worldPosition, perturbedNormals, tangentNormalized, viewDirection, albedo, specularity, roughness, metalicness);

	//vec4 cubecolor = texture (u_sampler3, reflect (-viewDirection, perturbedNormals));

    outColor = difSpec + emmit;
	//outBright = step (dot (outColor.xyz, vec3 (0.8, 0.8, 0.78)), 1.0) * outColor;
	if (dot (outColor.xyz, vec3 (0.8, 0.8, 0.78)) > 1.0)
	{
		outBright = vec4(outColor.rgb, 1.0);
	}

}
