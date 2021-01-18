#shader vertex
#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;

out vec2 TexCoords;

void main()
{
	TexCoords = inTexcoord;
	gl_Position = vec4(inPosition, 1.0);
}

#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D u_Texture;

void main()
{
	float depthValue = texture(u_Texture, TexCoords).r;
	FragColor = vec4(vec3(depthValue), 1.0);
}