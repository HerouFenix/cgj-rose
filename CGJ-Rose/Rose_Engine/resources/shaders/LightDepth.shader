#shader vertex
#version 330 core

in vec3 inPosition;

uniform mat4 ModelMatrix;

uniform LightInfo
{
	vec4 uniformLightColour;
	vec3 uniformLightPos;
	mat4 uniformLightViewMatrix;
	mat4 uniformLightProjMatrix;
};

void main(void)
{
	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = (uniformLightProjMatrix * uniformLightViewMatrix) * ModelMatrix * MCPosition;
}


#shader fragment
#version 330 core

void main(void)
{
}