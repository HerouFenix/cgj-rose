#include "../../../headers/shapes/Tetromino.h"

#include "../../../headers/vectors/Vector3.h"
#include "../../../headers/vectors/Vector4.h"
#include "../../../headers/matrices/Matrix4.h"

// Tetromino Constructors
Tetromino::Tetromino(float colour[4], Vector4 center) {
	// Set base square positions
	vertices[0].positions = Vector4(center.getX() - 0.10f, center.getY() - 0.05f, center.getZ(), 1.0f);
	vertices[1].positions = Vector4(center.getX() + 0.00f, center.getY() - 0.05f, center.getZ(), 1.0f);
	vertices[2].positions = Vector4(center.getX() + 0.00f, center.getY() + 0.05f, center.getZ(), 1.0f);
	vertices[3].positions = Vector4(center.getX() - 0.10f, center.getY() + 0.05f, center.getZ(), 1.0f);

	// Set base square colours
	float color[4] = { colour[0] / 256, colour[1] / 256, colour[2] / 256, colour[3] }; // Normalize RGB values
	vertices[0].colour[0] = color[0]; vertices[0].colour[1] = color[1]; vertices[0].colour[2] = color[2]; vertices[0].colour[3] = color[3];
	vertices[1].colour[0] = color[0]; vertices[1].colour[1] = color[1]; vertices[1].colour[2] = color[2]; vertices[1].colour[3] = color[3];
	vertices[2].colour[0] = color[0]; vertices[2].colour[1] = color[1]; vertices[2].colour[2] = color[2]; vertices[2].colour[3] = color[3];
	vertices[3].colour[0] = color[0]; vertices[3].colour[1] = color[1]; vertices[3].colour[2] = color[2]; vertices[3].colour[3] = color[3];

	// Define base transformations to create the figure from the base square
	Matrix4 identity = Matrix4::identity();
	transforms[0] = identity;

	identity[0][3] = 0.11f;
	transforms[1] = identity;

	identity[0][3] = 0.22f;
	transforms[2] = identity;

	identity[0][3] = -0.11f;
	transforms[3] = identity;

	rendered = false;
}

Tetromino::Tetromino(Vector4 center) {
	// Set base square positions
	vertices[0].positions = Vector4(center.getX() - 0.05f, center.getY() - 0.05f, center.getZ(), 1.0f);
	vertices[1].positions = Vector4(center.getX() + 0.05f, center.getY() - 0.05f, center.getZ(), 1.0f);
	vertices[2].positions = Vector4(center.getX() + 0.05f, center.getY() + 0.05f, center.getZ(), 1.0f);
	vertices[3].positions = Vector4(center.getX() - 0.05f, center.getY() + 0.05f, center.getZ(), 1.0f);
	/*vertices[0].positions = Vector4(center.getX() - 0.00f, center.getY() - 0.00f, center.getZ(), 1.0f);
	vertices[1].positions = Vector4(center.getX() + 0.10f, center.getY() - 0.00f, center.getZ(), 1.0f);
	vertices[2].positions = Vector4(center.getX() + 0.10f, center.getY() + 0.10f, center.getZ(), 1.0f);
	vertices[3].positions = Vector4(center.getX() - 0.00f, center.getY() + 0.10f, center.getZ(), 1.0f);*/

	// Set base square colours
	float r = (float)(rand() % 256) / 255;
	float g = (float)(rand() % 256) / 255;
	float b = (float)(rand() % 256) / 255;

	vertices[0].colour[0] = r; vertices[0].colour[1] = g; vertices[0].colour[2] = b; vertices[0].colour[3] = 1.0f;
	vertices[1].colour[0] = r; vertices[1].colour[1] = g; vertices[1].colour[2] = b; vertices[1].colour[3] = 1.0f;
	vertices[2].colour[0] = r; vertices[2].colour[1] = g; vertices[2].colour[2] = b; vertices[2].colour[3] = 1.0f;
	vertices[3].colour[0] = r; vertices[3].colour[1] = g; vertices[3].colour[2] = b; vertices[3].colour[3] = 1.0f;

	rendered = false;
}


void Tetromino::getVertices(VertexColour arr[4])
{
	arr[0] = vertices[0];
	arr[1] = vertices[1];
	arr[2] = vertices[2];
	arr[3] = vertices[3];
}


void Tetromino::getColours(float arr[4])
{
	arr[0] = vertices[0].colour[0];
	arr[1] = vertices[1].colour[1];
	arr[2] = vertices[2].colour[2];
	arr[3] = vertices[3].colour[3];
}

GLuint* Tetromino::getIndices()
{
	return indices;
}

void Tetromino::getIndices(GLuint arr[4])
{
	arr[0] = indices[0];
	arr[1] = indices[1];
	arr[2] = indices[2];
	arr[3] = indices[3];
}

void Tetromino::getReverseIndices(GLuint arr[4])
{
	arr[0] = indices[0];
	arr[1] = indices[3];
	arr[2] = indices[2];
	arr[3] = indices[1];
}

GLenum Tetromino::getMode()
{
	return mode;
}

Matrix4* Tetromino::getTransforms()
{
	return transforms;
}

void Tetromino::transform(Matrix4 transformMatrix)
{
	transforms[0] = transformMatrix * transforms[0];

	transforms[1] = transformMatrix * transforms[1];

	transforms[2] = transformMatrix * transforms[2];

	transforms[3] = transformMatrix * transforms[3];
}

void Tetromino::reset()
{
	return;
}

