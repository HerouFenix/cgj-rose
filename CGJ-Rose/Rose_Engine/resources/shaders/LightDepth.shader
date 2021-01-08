#shader vertex
#version 330 core

in vec3 inPosition;

uniform mat4 ModelMatrix;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;


void main(void)
{
	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = projMatrix * viewMatrix * ModelMatrix * MCPosition;
}


#shader fragment
#version 330 core

uniform vec4 uniformColour;
uniform vec4 uniformLightColour;
uniform vec3 uniformLightPos;
void main(void)
{
}