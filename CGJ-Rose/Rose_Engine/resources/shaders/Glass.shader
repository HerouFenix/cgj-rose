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

out vec3 exFragPos;
out vec3 exCameraPos;

out vec3 exLightPos;
out vec4 exLightColour;
out vec4 exFragPosLightSpace;

out vec3 v_reflection;
out vec3 v_refraction;
out float v_fresnel;

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

	exLightPos = uniformLightPos;
	exLightColour = uniformLightColour;

	vec4 MCPosition = vec4(inPosition, 1.0);
	vec4 camera_pos = vec4(1.0, 1.0, 1.0, 0.0) * ViewMatrix;
	exCameraPos.x = camera_pos.x;
	exCameraPos.y = camera_pos.y;
	exCameraPos.z = camera_pos.z;

	vec4 vertex = ViewMatrix * ModelMatrix * MCPosition;

	vec3 incident = normalize(vec3(vertex - camera_pos));
	v_refraction = refract(incident, exNormal, Eta);
	v_reflection = reflect(incident, exNormal);

	// see http://en.wikipedia.org/wiki/Schlick%27s_approximation
	v_fresnel = R0 + (1.0 - R0) * pow((1.0 - dot(-incident, exNormal)), 5.0);

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;
	exFragPos = vec3(ModelMatrix * MCPosition);
	exFragPosLightSpace = uniformLightSpace * vec4(exFragPos, 1.0);
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
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

	return shadow;
}

void main(void)
{


	// Ambient
	float ambientStrength = 0.4;
	vec4 ambient = exLightColour;
	ambient.x = ambient.x * ambientStrength;
	ambient.y = ambient.y * ambientStrength;
	ambient.z = ambient.z * ambientStrength;

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
	shadow = 0;
	vec4 color = (ambient + (1.0 - shadow) * (diffuse + specular)) * uniformColour;


	float antiRefractionValue = 0.6;
	vec4 refractionColor = texture(skybox, normalize(v_refraction));
	//refractionColor = (refractionColor + uniformColour)/2;
	refractionColor = color * antiRefractionValue + refractionColor * (1 - antiRefractionValue);


	float antiReflectionValue = 0.63;
	vec4 reflectionColor = texture(skybox, normalize(v_reflection));
	//reflectionColor = (reflectionColor+uniformColour)/2;
	reflectionColor = color * antiReflectionValue + reflectionColor * (1 - antiReflectionValue);



	out_Color = mix(refractionColor, reflectionColor, v_fresnel);
}