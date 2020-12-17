#shader vertex
#version 330 core

// Indices of refraction
const float Air = 1.0;
const float Glass = 1.51714;

// Air to glass ratio of the indices of refraction (Eta)
const float Eta = Air / Glass;

// see http://en.wikipedia.org/wiki/Refractive_index Reflectivity
const float R0 = ((Air - Glass) * (Air - Glass)) / ((Air + Glass) * (Air + Glass));

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;

out vec3 v_reflection;
out vec3 v_refraction;
out float v_fresnel;

uniform mat4 ModelMatrix;

uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void)
{
	exPosition = inPosition;
	exTexcoord = inTexcoord;
	exNormal = inNormal;
	vec4 MCPosition = vec4(inPosition, 1.0);
	vec4 camera_pos = vec4(1.0, 1.0, 1.0, 0.0) * ViewMatrix;

	vec4 vertex = ViewMatrix * ModelMatrix * MCPosition;
	
	vec3 incident = normalize(vec3(vertex - camera_pos));
	v_refraction = refract(incident, exNormal, Eta);
	v_reflection = reflect(incident, exNormal);
	
	// see http://en.wikipedia.org/wiki/Schlick%27s_approximation
	v_fresnel = R0 + (1.0 - R0) * pow((1.0 - dot(-incident, exNormal)), 5.0);

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;
}

#shader fragment
#version 330 core

in vec4 ex_Color;
out vec4 out_Color;

uniform int isBack;

uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;
uniform float Shininess;

in vec3 v_refraction;
in vec3 v_reflection;
in float v_fresnel;

uniform samplerCube skybox;
uniform vec4 uniformColour;

void main(void)
{

	float antiRefractionValue = 0.6;
	vec4 refractionColor = texture(skybox, normalize(v_refraction));
	//refractionColor = (refractionColor + uniformColour)/2;
	refractionColor = uniformColour * antiRefractionValue + refractionColor * (1 - antiRefractionValue);


	float antiReflectionValue = 0.63;
	vec4 reflectionColor = texture(skybox, normalize(v_reflection));
	//reflectionColor = (reflectionColor+uniformColour)/2;
	reflectionColor = uniformColour * antiReflectionValue + reflectionColor * (1 - antiReflectionValue);
	
	out_Color = mix(refractionColor, reflectionColor, v_fresnel);
}