#shader vertex
#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;

out mat4 exLightViewMatrix;
out mat4 exLightProjMatrix;
out vec3 exLightPos;
out vec4 exLightColour;

out vec3 exFragPos;
out vec3 exCameraPos;

uniform mat4 ModelMatrix;

uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

uniform LightInfo
{
	vec4 uniformLightColour;
	vec3 uniformLightPos;
	mat4 uniformLightViewMatrix;
	mat4 uniformLightProjMatrix;
};

void main(void)
{
	exPosition = inPosition;
	exTexcoord = inTexcoord;
	exNormal = inNormal;
	exNormal = mat3(transpose(inverse(ModelMatrix))) * inNormal;

	exLightViewMatrix = uniformLightViewMatrix;
	exLightProjMatrix = uniformLightProjMatrix;
	exLightPos = uniformLightPos;
	exLightColour = uniformLightColour;

	vec4 cameraPos = vec4(1.0, 1.0, 1.0, 0.0) * ViewMatrix;
	exCameraPos.x = cameraPos.x;
	exCameraPos.y = cameraPos.y;
	exCameraPos.z = cameraPos.z;

	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;

	exFragPos = vec3(ModelMatrix * MCPosition);
}

#shader fragment
#version 330 core

in vec4 ex_Color;
in vec2 exTexcoord;

out vec4 out_Color;

uniform int isBack;

uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;
uniform float Shininess;


in mat4 exLightViewMatrix;
in mat4 exLightProjMatrix;
in vec3 exLightPos;
in vec4 exLightColour;

in vec3 exNormal;
in vec3 exFragPos;
in vec3 exCameraPos;


float random(in vec2 st) {
	return fract(sin(dot(st.xy, vec2(13, 78))) * 43758);
}

float noise(vec2 st) {
	vec2 i = floor(st);
	vec2 f = fract(st);
	vec2 u = f * f * (3.0 - 2.0 * f);
	return mix(mix(random(i + vec2(0.0, 0.0)),
		random(i + vec2(1.0, 0.0)), u.x),
		mix(random(i + vec2(0.0, 1.0)),
			random(i + vec2(1.0, 1.0)), u.x), u.y);
}

mat2 rotate2d(float angle) {
	return mat2(cos(angle), -sin(angle),
		sin(angle), cos(angle));
}

float lines(in vec2 pos, float b) {
	float scale = 10.0;
	pos *= scale;
	return smoothstep(0.0,
		.5 + b * .5,
		abs((sin(pos.x * 3.1415) + b * 2.0)) * .5);
}

void main(void) {
	float t = 1.0;
	vec2 st = exTexcoord;
	st.x *= 1000. / 600.;
	vec3 color = vec3(0.654, 0.419, 0.467);
	st += noise(st * 2.) * t; // Animate the coordinate space
	//color += vec3(1.) * smoothstep(.18,.2,noise(st)); // Big black drops
	color += smoothstep(.15, .35, noise(st * 10.1)); // Black splatter
	color -= smoothstep(.05, .4, noise(st * 10.1)); // Holes on splatter

	// Ambient
	float ambientStrength = 0.1;
	vec4 ambient = exLightColour;
	ambient.x = ambient.x * 0.1;
	ambient.y = ambient.y * 0.1;
	ambient.z = ambient.z * 0.1;

	// Diffuse
	vec3 norm = normalize(exNormal);

	vec3 lightDir = normalize(exLightPos - exFragPos);
	vec3 viewDir = normalize(exCameraPos - exFragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);

	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * exLightColour;

	// Specular
	vec3 reflectDir = reflect(-lightDir, norm);

	int shininess = 32;

	float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
	vec4 specular = exLightColour * spec;

	out_Color = vec4(color, 1.0) * (ambient + diffuse + specular);
}