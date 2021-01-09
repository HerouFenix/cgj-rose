#shader vertex
#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;

out vec3 exFragPos;
out vec3 exCameraPos;

out mat4 exLightViewMatrix;
out mat4 exLightProjMatrix;
out vec3 exLightPos;
out vec4 exLightColour;

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

uniform sampler2D u_Texture;

in mat4 exLightViewMatrix;
in mat4 exLightProjMatrix;
in vec3 exLightPos;
in vec4 exLightColour;
uniform vec4 uniformColour;

in vec3 exNormal;
in vec3 exFragPos;
in vec3 exCameraPos;


void main(void)
{
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


	vec4 color = (ambient + diffuse + specular) * uniformColour;
	out_Color = texture(u_Texture, exTexcoord) * color;
}