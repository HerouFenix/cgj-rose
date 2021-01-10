#shader vertex
#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;

out vec3 exLightPos;
out vec4 exLightColour;

out vec3 exFragPos;
out vec3 exCameraPos;
out vec4 exFragPosLightSpace;

uniform mat4 ModelMatrix;

uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

uniform LightInfo
{
	mat4 uniformLightSpace;
	vec4 uniformLightColour;
	vec3 uniformLightPos;
};

out mat4 lightSpaceThingy;

void main(void)
{
	exPosition = inPosition;
	exTexcoord = inTexcoord;
	exNormal = inNormal;
	exNormal = mat3(transpose(inverse(ModelMatrix))) * inNormal;

	exLightPos = uniformLightPos;
	exLightColour = uniformLightColour;

	vec4 cameraPos = vec4(1.0, 1.0, 1.0, 0.0) * ViewMatrix;
	exCameraPos.x = cameraPos.x;
	exCameraPos.y = cameraPos.y;
	exCameraPos.z = cameraPos.z;

	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;

	exFragPos = vec3(ModelMatrix * MCPosition);
	exFragPosLightSpace = uniformLightSpace * vec4(exFragPos, 1.0);
	lightSpaceThingy = uniformLightSpace;
}

#shader fragment
#version 330 core

in vec2 exTexcoord;

out vec4 out_Color;

uniform int isBack;

uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;
uniform float Shininess;

uniform sampler2D u_Texture;
uniform sampler2D shadowMap;

uniform vec4 uniformColour;

in vec3 exNormal;
in vec3 exFragPos;
in vec3 exCameraPos;

in vec3 exLightPos;
in vec4 exLightColour;
in vec4 exFragPosLightSpace;

in mat4 lightSpaceThingy;

float ShadowCalculation(vec4 fragPosLightSpace)
{
	// perform perspective divide
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	// transform to [0,1] range
	projCoords = projCoords * 0.5 + 0.5;
	// get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	// get depth of current fragment from light's perspective
	float currentDepth = projCoords.z;
	// check whether current frag pos is in shadow
	float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

	return shadow;
}


void main(void)
{
	//vec4 color = exLightColour * uniformColour;
	//out_Color = color;

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
	//float specularStrength = 0.5;
	vec3 reflectDir = reflect(-lightDir, norm);

	int shininess = 32;
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	//vec4 specular = specularStrength * spec * exLightColour;

	float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
	vec4 specular = exLightColour * spec;

	// calculate shadow
	float shadow = ShadowCalculation(exFragPosLightSpace);
	//shadow = 0;
	vec4 color = (ambient + (1.0 - shadow) * (diffuse + specular)) * uniformColour;

	//if (lightSpaceThingy == 0) {
	//	out_Color = vec4(1.0, 0.0, 0.0, 1.0);
	//}
	//else {
	//	out_Color = vec4(1.0, 1.0, 0.0, 1.0);
	//}
	out_Color = color;
}