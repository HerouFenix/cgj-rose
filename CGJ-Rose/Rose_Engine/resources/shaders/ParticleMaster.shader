#shader vertex
#version 330

in vec3 position;


void main(void) {
    gl_Position = vec4(position, 1.0);
}

#shader geometry
#version 150

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

const float size = 0.01;

void createVertex(vec3 offset) {
    vec4 actualOffset = vec4(offset * size, 0.0);
    vec4 worldPosition = gl_in[0].gl_Position + actualOffset;
    gl_Position = ProjectionMatrix * ViewMatrix * worldPosition;
    EmitVertex();
}


void main(void) {

	createVertex(vec3(-1.0, 1.0, 1.0));
	createVertex(vec3(-1.0, -1.0, 1.0));
	createVertex(vec3(1.0, 1.0, 1.0));
	createVertex(vec3(1.0, -1.0, 1.0));

	EndPrimitive();

	createVertex(vec3(1.0, 1.0, 1.0));
	createVertex(vec3(1.0, -1.0, 1.0));
	createVertex(vec3(1.0, 1.0, -1.0));
	createVertex(vec3(1.0, -1.0, -1.0));

	EndPrimitive();

	createVertex(vec3(1.0, 1.0, -1.0));
	createVertex(vec3(1.0, -1.0, -1.0));
	createVertex(vec3(-1.0, 1.0, -1.0));
	createVertex(vec3(-1.0, -1.0, -1.0));

	EndPrimitive();

	createVertex(vec3(-1.0, 1.0, -1.0));
	createVertex(vec3(-1.0, -1.0, -1.0));
	createVertex(vec3(-1.0, 1.0, 1.0));
	createVertex(vec3(-1.0, -1.0, 1.0));

	EndPrimitive();

	createVertex(vec3(1.0, 1.0, 1.0));
	createVertex(vec3(1.0, 1.0, -1.0));
	createVertex(vec3(-1.0, 1.0, 1.0));
	createVertex(vec3(-1.0, 1.0, -1.0));

	EndPrimitive();

	createVertex(vec3(-1.0, -1.0, 1.0));
	createVertex(vec3(-1.0, -1.0, -1.0));
	createVertex(vec3(1.0, -1.0, 1.0));
	createVertex(vec3(1.0, -1.0, -1.0));

	EndPrimitive();
}

#shader fragment
#version 330

uniform vec4 u_Color;

out vec4 out_Colour;

void main(void) {

    out_Colour = u_Color;

}