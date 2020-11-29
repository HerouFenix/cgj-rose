#include "../../../headers/shapes/Tetromino.h"

#include "../../../headers/vectors/Vector3.h"
#include "../../../headers/vectors/Vector4.h"
#include "../../../headers/matrices/Matrix4.h"


// Tetromino SQ Constructors
Tetromino_SQ::Tetromino_SQ(float colour[4], Vector4 center) : Tetromino(colour, center) {

	// Define base transformations to create the figure from the base square
	Matrix4 identity = Matrix4::identity();
	transforms[0] = identity;

	identity[1][3] = 2.2f;
	transforms[1] = identity;

	identity[0][3] = 2.2f;
	transforms[2] = identity;

	identity[1][3] = 0.00f;
	transforms[3] = identity;
}

Tetromino_SQ::Tetromino_SQ(Vector4 center) :Tetromino(center)
{
	// Define base transformations to create the figure from the base square
	Matrix4 identity = Matrix4::identity();
	transforms[0] = identity;

	identity[1][3] = 2.2f;
	transforms[1] = identity;

	identity[0][3] = 2.2f;
	transforms[2] = identity;

	identity[1][3] = 0.00f;
	transforms[3] = identity;
}

void Tetromino_SQ::reset()
{
	Matrix4 identity = Matrix4::identity();
	transforms[0] = identity;

	identity[1][3] = 2.2f;
	transforms[1] = identity;

	identity[0][3] = 2.2f;
	transforms[2] = identity;

	identity[1][3] = 0.00f;
	transforms[3] = identity;
}

