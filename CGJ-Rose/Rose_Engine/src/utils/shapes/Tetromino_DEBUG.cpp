#include "../../../headers/shapes/Tetromino.h"

#include "../../../headers/vectors/Vector3.h"
#include "../../../headers/vectors/Vector4.h"
#include "../../../headers/matrices/Matrix4.h"


Tetromino_DEBUG::Tetromino_DEBUG(){
	// Set base square positions
	vertices[0].positions = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	vertices[1].positions = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
	vertices[2].positions = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	vertices[3].positions = Vector4(0.0f, 1.0f, 1.0f, 1.0f);

	// Set base square colours
	vertices[0].colour[0] = 0.9f; vertices[0].colour[1] = 0.0f; vertices[0].colour[2] = 0.0f; vertices[0].colour[3] = 1.0f;
	vertices[1].colour[0] = 0.9f; vertices[1].colour[1] = 0.0f; vertices[1].colour[2] = 0.0f; vertices[1].colour[3] = 1.0f;
	vertices[2].colour[0] = 0.9f; vertices[2].colour[1] = 0.0f; vertices[2].colour[2] = 0.0f; vertices[2].colour[3] = 1.0f;
	vertices[3].colour[0] = 0.9f; vertices[3].colour[1] = 0.0f; vertices[3].colour[2] = 0.0f; vertices[3].colour[3] = 1.0f;

	// Define base transformations to create the figure from the base square
	Matrix4 identity = Matrix4::identity();
	transforms[0] = identity;
}