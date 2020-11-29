#version 330 core

in vec3 exPosition;
in vec2 exTexcoord;
in vec3 exNormal;

out vec4 FragmentColor;
uniform vec4 ourColor;

void main(void)
{
	FragmentColor = ourColor;
}
