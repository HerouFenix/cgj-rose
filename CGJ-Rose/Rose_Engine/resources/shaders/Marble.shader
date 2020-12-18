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

	vec4 MCPosition = vec4(inPosition, 1.0);
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * MCPosition;
}

#shader fragment
#version 330 core

in vec4 ex_Color;
in vec2 exTexcoord;

out vec4 out_Color;

uniform int isBack;

uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;
uniform float Shininess;


uniform vec4 uniformColour;

float random(in vec2 st) {
	return fract(sin(dot(st.xy, vec2(13, 78))) * 43758);
}

float noise(vec2 st) {
	vec2 i = floor(st);
	vec2 f = fract(st);
	vec2 u = f * f * (3.0 - 2.0 * f);
	return mix(mix(random(i + vec2(0.0, 0.0)),
		random(i + vec2(1.0, 0.0)), u.x),
		mix(random(i + vec2(0.0, 1.0)),
			random(i + vec2(1.0, 1.0)), u.x), u.y);
}

mat2 rotate2d(float angle) {
	return mat2(cos(angle), -sin(angle),
		sin(angle), cos(angle));
}

float lines(in vec2 pos, float b) {
	float scale = 10.0;
	pos *= scale;
	return smoothstep(0.0,
		.5 + b * .5,
		abs((sin(pos.x * 3.1415) + b * 2.0)) * .5);
}

void main(void) {
	float t = 1.0;
	vec2 st = exTexcoord;
	st.x *= 1000. / 600.;
	vec3 color = vec3(0.654, 0.419, 0.467);
	st += noise(st * 2.) * t; // Animate the coordinate space
	//color += vec3(1.) * smoothstep(.18,.2,noise(st)); // Big black drops
	color += smoothstep(.15, .35, noise(st * 10.1)); // Black splatter
	color -= smoothstep(.05, .4, noise(st * 10.1)); // Holes on splatter

	out_Color = vec4(color, 1.0);
}