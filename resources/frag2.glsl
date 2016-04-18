#version 410

layout(location = 1) in vec3 v_normal;
layout(location = 0) in vec2 v_texcoord;
layout(location = 2) in vec3 v_worldPosition;

layout(location = 0) out vec4 outColor;

uniform sampler2D u_sampler0;
uniform vec3 u_camPosition;


struct DirectionalLight {
	vec3 color;
	float intensity;
	vec3 direction;
};


void main()
{

	DirectionalLight sun = DirectionalLight (
		vec3 (1.0, 1.0, 0.93),
		1.0,
		vec3 (-0.15, -0.1, -0.9)
	);

	//vec3 u_camPosition = vec3 (-5.0, 0.0, 0.0);
	vec4 ambientLight = vec4 (0.1, 0.06, 0.15, 1.0) * 2;
	vec3 sunNormalized = normalize (sun.direction);
	vec3 normalNormalized = normalize (v_normal);
	vec3 viewDirection = normalize (u_camPosition - v_worldPosition);
	//gl_FragDepth = gl_FragCoord.z;

	vec3 HalfDirection = normalize ((sunNormalized - viewDirection)*0.5);

	float lightness = max (0.0, dot (-sunNormalized, normalNormalized)) + 2.0 * texture(u_sampler0, v_texcoord.st).w * pow (max (0.0, dot (-HalfDirection, normalNormalized)) , 100.0);
    outColor = texture(u_sampler0, v_texcoord.st) * (lightness + ambientLight);

}
