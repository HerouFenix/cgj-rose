#shader vertex
#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;
out vec3 fNormal;

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


	mat3 normalMatrix = mat3(transpose(inverse(ViewMatrix * ModelMatrix)));

	fNormal = normalize(normalMatrix * inNormal);
	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;

	exFragPos = vec3(ModelMatrix * MCPosition);
}

#shader fragment
#version 330 core

in vec4 ex_Color;
in vec3 fNormal;
in vec2 exTexcoord;

out vec4 FragColor;

uniform int isBack;

uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;
uniform float Shininess;

uniform float time_U;
uniform sampler2D u_Texture;

in mat4 exLightViewMatrix;
in mat4 exLightProjMatrix;
in vec3 exLightPos;
in vec4 exLightColour;


in vec3 exNormal;
in vec3 exFragPos;
in vec3 exCameraPos;



void main(void)
{
	float theta = time_U * 0.8f;

	vec3 dir1 = vec3(sin(theta), 0, cos(theta));
	vec3 dir2 = vec3(cos(theta), 0, sin(theta));

	float diffuse1 = pow(dot(fNormal, dir1), 2.0);
	float diffuse2 = pow(dot(fNormal, dir2), 2.0);

	vec3 col1 = diffuse1 * vec3(1, 0, 0);
	vec3 col2 = diffuse2 * vec3(1, 0, 1);
	vec4 col = vec4(col1 + col2, 1.0) * 8.0f;


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

	FragColor = texture(u_Texture, exTexcoord) * col * (ambient + diffuse + specular);
	//out_Color = vec4(col1 + col2, 1.0);
}