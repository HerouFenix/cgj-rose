#shader vertex
#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;

out vec3 exFragPos;

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
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;

	exFragPos = vec3(ModelMatrix * MCPosition);
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

uniform vec4 uniformColour;
uniform vec4 uniformLightColour;
uniform vec3 uniformLightPos;

in vec3 exNormal;
in vec3 exFragPos;

void main(void)
{
	//vec4 color = uniformLightColour * uniformColour;
	//out_Color = color;

	float ambientStrength = 0.1;
	vec4 ambient = uniformLightColour;
	ambient.x = ambient.x * 0.1;
	ambient.y = ambient.y * 0.1;
	ambient.z = ambient.z * 0.1;

	vec3 norm = normalize(exNormal);
	vec3 lightDir = normalize(uniformLightPos - exFragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = diff * uniformLightColour;

	vec4 color = (ambient + diffuse) * uniformColour;
	out_Color = color;



}