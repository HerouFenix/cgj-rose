#shader vertex
#version 330 core

in vec3 inPosition;

uniform mat4 ModelMatrix;

uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(void)
{

	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;

}

#shader fragment
#version 330 core

out vec4 out_Color;
uniform vec4 u_Color;

void main(void)
{
	out_Color = u_Color;
}