#shader vertex
#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

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
	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;	
}

#shader fragment
#version 330 core

out vec4 out_Color;

void main(void)
{
	
	out_Color = vec4(1.0);
}