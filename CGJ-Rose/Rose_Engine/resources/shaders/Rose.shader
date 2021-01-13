#shader vertex
#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;
out vec3 fNormal;

out vec3 exLightPos;
out vec4 exLightColour;
out vec4 exFragPosLightSpace;

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
	mat4 uniformLightSpace;
	vec4 uniformLightColour;
	vec3 uniformLightPos;
};

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


	mat3 normalMatrix = mat3(transpose(inverse(ViewMatrix * ModelMatrix)));

	fNormal = normalize(normalMatrix * inNormal);
	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;

	exFragPos = vec3(ModelMatrix * MCPosition);
	exFragPosLightSpace = uniformLightSpace * vec4(exFragPos, 1.0);
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

in vec3 exLightPos;
in vec4 exLightColour;
in vec4 exFragPosLightSpace;

uniform sampler2D shadowMap;


in vec3 exNormal;
in vec3 exFragPos;
in vec3 exCameraPos;

float ShadowCalculation(vec4 fragPosLightSpace, vec3 exNormal, vec3 exLightPos)
{
	// perform perspective divide
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	// transform to [0,1] range
	projCoords = projCoords * 0.5 + 0.5;
	// get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	// get depth of current fragment from light's perspective
	float currentDepth = projCoords.z;
	//Bias variable to fix shadow acne
	float bias = max(0.05 * (1.0 - dot(exNormal, exLightPos)), 0.005);
	// check whether current frag pos is in shadow
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}

	if (projCoords.z > 1.0)
		shadow = 0.0;

	return shadow;
}


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
	float ambientStrength = 0.4;
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

	// calculate shadow
	float shadow = ShadowCalculation(exFragPosLightSpace, exNormal, exLightPos);

	FragColor = texture(u_Texture, exTexcoord) * col * (ambient + (1.0 - shadow) * (diffuse + specular));
	//out_Color = vec4(col1 + col2, 1.0);
}