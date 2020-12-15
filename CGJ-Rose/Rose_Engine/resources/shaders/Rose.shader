#shader vertex
#version 330 core

in vec3 inPosition;
in vec2 inTexcoord;
in vec3 inNormal;

out vec3 exPosition;
out vec2 exTexcoord;
out vec3 exNormal;
out vec3 fNormal;


uniform mat4 ModelMatrix;

uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

uniform float time;


void main(void)
{
	exPosition = inPosition;
	exTexcoord = inTexcoord;
	exNormal = inNormal;

	mat3 normalMatrix = mat3(transpose(inverse(ViewMatrix * ModelMatrix)));

	fNormal = normalize(normalMatrix * inNormal);
	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;
}

#shader fragment
#version 330 core

in vec4 ex_Color;
in vec3 fNormal;
in vec2 exTexcoord;

out vec4 out_Color;

uniform int isBack;

uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;
uniform float Shininess;

uniform float time_U;
uniform sampler2D u_Texture;


void main(void)
{
	float theta = time_U * 0.5f;

	vec3 dir1 = vec3(sin(theta), 0, cos(theta));
	vec3 dir2 = vec3(cos(theta), 0, sin(theta));

	float diffuse1 = pow(dot(fNormal, dir1), 2.0);
	float diffuse2 = pow(dot(fNormal, dir2), 2.0);

	vec3 col1 = diffuse1 * vec3(1, 0, 0);
	vec3 col2 = diffuse2 * vec3(1, 0, 1);

	out_Color = texture(u_Texture, exTexcoord);
	//out_Color = vec4(col1 + col2, 1.0);
}