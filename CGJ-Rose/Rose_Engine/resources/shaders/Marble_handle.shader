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

//in vec3 exPosition;

in vec3 exLightPos;
in vec4 exLightColour;
in vec4 exFragPosLightSpace;

in vec3 exNormal;
in vec3 exFragPos;
in vec3 exCameraPos;

//uniform vec3 viewPos;

//uniform vec3 lightSource;

uniform vec4 uniformColour;

uniform sampler2D shadowMap;

const vec3 tileSize = vec3(1.1, 1.0, 1.1);
const vec3 tilePct = vec3(0.98, 1.0, 0.98);

float mod289(float x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec4 mod289(vec4 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec4 perm(vec4 x) { return mod289(((x * 34.0) + 1.0) * x); }

float noise(vec3 p) {  //simplex noise
	vec3 a = floor(p);
	vec3 d = p - a;
	d = d * d * (3.0 - 2.0 * d);

	vec4 b = a.xxyy + vec4(0.0, 1.0, 0.0, 1.0);
	vec4 k1 = perm(b.xyxy);
	vec4 k2 = perm(k1.xyxy + b.zzww);

	vec4 c = k2 + a.zzzz;
	vec4 k3 = perm(c);
	vec4 k4 = perm(c + 1.0);

	vec4 o1 = fract(k3 * (1.0 / 41.0));
	vec4 o2 = fract(k4 * (1.0 / 41.0));

	vec4 o3 = o2 * d.z + o1 * (1.0 - d.z);
	vec2 o4 = o3.yw * d.x + o3.xz * (1.0 - d.x);

	return o4.y * d.y + o4.x * (1.0 - d.y);
}

float turbulence(vec3 P, int numFreq)
{
	float val = 0.0;
	float freq = 1.0;
	for (int i = 0; i < numFreq; i++) {
		val += abs(noise(P * freq) / freq);
		freq *= 2.07;
	}
	return val;
}

vec3 marble_color(float x)
{
	vec3 col;
	x = 0.5 * (x + 1.);          // transform -1<x<1 to 0<x<1
	x = sqrt(x);             // make x fall of rapidly...
	x = sqrt(x);
	x = sqrt(x);
	col = vec3(.2 + .75 * x);  // scale x from 0<x<1 to 0.2<x<0.95
	col.b *= 0.95;             // slightly reduce blue component (make color "warmer"):
	return col;
}

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

	float bias = max(0.05 * (1.0 - dot(exNormal, exLightPos)), 0.005);

	// check whether current frag pos is in shadow
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

	if (projCoords.z > 1.0)
		shadow = 0.0;

	return shadow;
}

void main()
{
	vec3 color = vec3(0.43f, 0.31f, 0.43f);

	// ambient
	float ambientStrength = 0.4;
	vec4 ambient = exLightColour;
	ambient.x = ambient.x * 0.1;
	ambient.y = ambient.y * 0.1;
	ambient.z = ambient.z * 0.1;

	// diffuse 
	vec3 norm = normalize(exNormal);

	vec3 lightDir = normalize(exLightPos - exFragPos);
	vec3 viewDir = normalize(exCameraPos - exFragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);

	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * exLightColour;

	// specular
	vec3 reflectDir = reflect(-lightDir, norm);

	int shininess = 32;

	float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
	vec4 specular = exLightColour * spec;

	// calculate shadow
	float shadow = ShadowCalculation(exFragPosLightSpace, exNormal, exLightPos);

	float amplitude = 50.0;
	const int roughness = 7;     // noisiness of veins (#octaves in turbulence)

	float t = 6.28 * exFragPos.x / tileSize.x;
	t += amplitude * turbulence(exFragPos.xyz, roughness);
	// replicate over rows of tiles (wont be identical, because noise is depending on all coordinates of the input vector):
	t = sin(t);
	out_Color = vec4(marble_color(t), 1.0) * vec4(color, 1.0) * (ambient + (1.0 - shadow) * (diffuse + specular));

}