#shader vertex
#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;

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

	vec4 MCPosition = vec4(inPosition, 0.5);
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

uniform vec4 uniformColour;

void main(void)
{
	out_Color = uniformColour;
}