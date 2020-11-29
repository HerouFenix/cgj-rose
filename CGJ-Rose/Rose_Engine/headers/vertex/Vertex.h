#pragma once

#include "../vectors/Vector4.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct
{
	Vector4 positions;
	float colour[4];
} VertexColour;

typedef struct {
	GLfloat x, y, z;
} Vertex;

typedef struct {
	GLfloat u, v;
} Texcoord;

typedef struct {
	GLfloat nx, ny, nz;
} Normal;