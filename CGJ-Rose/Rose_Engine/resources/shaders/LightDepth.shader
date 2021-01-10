#shader vertex
#version 330 core

in vec3 inPosition;

uniform mat4 ModelMatrix;

uniform LightInfo
{
	mat4 uniformLightSpace;
	vec4 uniformLightColour;
	vec3 uniformLightPos;
};

//uniform mat4 lightSpace;

void main(void)
{
	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = uniformLightSpace * ModelMatrix * MCPosition;
}


#shader fragment
#version 330 core

void main(void)
{
}