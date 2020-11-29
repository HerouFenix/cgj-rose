#include "../../../headers/matrices/Matrix2.h"
#include "../../../headers/matrices/Matrix3.h"
#include "../../../headers/matrices/Matrix4.h"

#include "../../../headers/vectors/Vector2.h"

#include <cassert>

// Matrix 2 Constructors
Matrix2::Matrix2() {
}

Matrix2::Matrix2(float val) {
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matrix[row][col] = val;
		}
	}
}

Matrix2::Matrix2(float mat[2][2]) {
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matrix[row][col] = mat[row][col];
		}
	}
}

Matrix2::Matrix2(Matrix3& mat) {
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matrix[row][col] = mat[row][col];
		}
	}
}

Matrix2::Matrix2(Matrix4& mat) {
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matrix[row][col] = mat[row][col];
		}
	}
}

//Matrix2 Print
std::ostream& operator<<(std::ostream& os, const Matrix2& matrix)
{
	os << "\n";
	for (int row = 0; row < 2; row++) {
		os << "[";

		for (int col = 0; col < 2; col++) {
			os << matrix.matrix[row][col];
			if (col != 1) {
				os << ", ";
			}
		}
		os << "]\n";
	}
	return os;
}


//Clone
Matrix2 Matrix2::clone() {
	return Matrix2(matrix);
}

//Matrix2 Getters
float Matrix2::get(int row, int col) {
	assert(row > 0 && row < 2 && col > 0 && col < 2);
	return matrix[row][col];
}

void Matrix2::getRowMajor(float* arr) {
	int index = 0;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			arr[index++] = matrix[row][col];
		}
	}
}

void Matrix2::getColMajor(float* arr) {
	int index = 0;
	for (int col = 0; col < 2; col++) {
		for (int row = 0; row < 2; row++) {
			arr[index++] = matrix[row][col];
		}
	}
}

//Matrix2 Setters
void Matrix2::set(int row, int col, float val) {
	assert(row >= 0 && row < 2 && col >= 0 && col < 2);
	matrix[row][col] = val;
}


//Matrix2 Operations
float* Matrix2::operator[](int val) {
	return matrix[val];
}

Matrix2 Matrix2::operator+(const Matrix2& mat)
{
	/* NEEDLESS ASSERTION
	int noRows = sizeof(mat.matrix) / sizeof(mat.matrix[0]);
	int noCols = sizeof(mat.matrix[0]) / sizeof(float);
	std::cout << noRows << "\n";
	assert(noRows == 2 && noCols == 2);
	*/

	Matrix2 matSum;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matSum.matrix[row][col] = matrix[row][col] + mat.matrix[row][col];
		}
	}

	return matSum;
}

Matrix2 Matrix2::operator+(float val) {
	Matrix2 matSum;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matSum.matrix[row][col] = matrix[row][col] + val;
		}
	}

	return matSum;
}

Matrix2 operator+(float val, Matrix2& mat) {
	Matrix2 matSum;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matSum.matrix[row][col] = mat.matrix[row][col] + val;
		}
	}

	return matSum;
}

Matrix2 Matrix2::operator-(const Matrix2& mat)
{
	Matrix2 matSub;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matSub.matrix[row][col] = matrix[row][col] - mat.matrix[row][col];
		}
	}

	return matSub;
}

Matrix2 Matrix2::operator-(float val) {
	Matrix2 matSum;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matSum.matrix[row][col] = matrix[row][col] - val;
		}
	}

	return matSum;
}

Matrix2 operator-(float val, Matrix2& mat) {
	Matrix2 matSub;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matSub.matrix[row][col] = val - mat.matrix[row][col];
		}
	}

	return matSub;
}

Matrix2 Matrix2::operator*(const Matrix2& mat) {
	Matrix2 matMul;

	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			for (int i = 0; i < 2; ++i)
			{
				matMul.matrix[row][col] += matrix[row][i] * mat.matrix[i][col];
			}
		}
	}

	return matMul;
}

Matrix2 Matrix2::operator*(float val)
{
	Matrix2 matMul;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matMul.matrix[row][col] = matrix[row][col] * val;
		}
	}

	return matMul;
}

Matrix2 operator*(float val, Matrix2& mat)
{
	Matrix2 matMul;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matMul.matrix[row][col] = mat.matrix[row][col] * val;
		}
	}

	return matMul;
}

Vector2 Matrix2::operator*(Vector2& vec) {
	float x = matrix[0][0] * vec.getX() + matrix[0][1] * vec.getY();

	float y = matrix[1][0] * vec.getX() + matrix[1][1] * vec.getY();

	return Vector2(x, y);
}

Vector2 operator*(Vector2& vec, Matrix2& mat) {
	float x = vec.getX() * mat.matrix[0][0] + vec.getY() * mat.matrix[1][0];

	float y = vec.getX() * mat.matrix[0][1] + vec.getY() * mat.matrix[1][1];

	return Vector2(x, y);
}

Matrix2 Matrix2::operator/(float val)
{
	Matrix2 matMul;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matMul.matrix[row][col] = matrix[row][col] / val;
		}
	}

	return matMul;
}

Matrix2 operator/(float val, Matrix2& mat)
{
	Matrix2 matMul;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matMul.matrix[row][col] = val/mat.matrix[row][col];
		}
	}

	return matMul;
}

//Matrix2 Assignments
Matrix2& Matrix2::operator+=(const Matrix2& mat) {
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matrix[row][col] = matrix[row][col] + mat.matrix[row][col];
		}
	}

	return *this;
}

Matrix2& Matrix2::operator+=(float val) {
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matrix[row][col] = matrix[row][col] + val;
		}
	}

	return *this;
}

Matrix2& Matrix2::operator-=(const Matrix2& mat) {
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matrix[row][col] = matrix[row][col] - mat.matrix[row][col];
		}
	}

	return *this;
}

Matrix2& Matrix2::operator-=(float val) {
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matrix[row][col] = matrix[row][col] - val;
		}
	}

	return *this;
}

Matrix2& Matrix2::operator*=(const Matrix2& mat) {
	return *this = *this * mat;
}

Matrix2& Matrix2::operator*=(float val) {
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matrix[row][col] = matrix[row][col] * val;
		}
	}

	return *this;
}

Vector2 operator*=(Vector2& vec, Matrix2& mat) {
	vec.setX(vec.getX() * mat.matrix[0][0] + vec.getY() * mat.matrix[1][0]);

	vec.setY(vec.getX() * mat.matrix[0][1] + vec.getY() * mat.matrix[1][1]);

	return vec;
}

Matrix2& Matrix2::operator/=(float val) {
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matrix[row][col] = matrix[row][col] / val;
		}
	}

	return *this;
}

Matrix2& Matrix2::operator=(const Matrix2& mat) {
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matrix[row][col] = mat.matrix[row][col];
		}
	}

	return *this;
}

Matrix2& Matrix2::operator=(float val) {
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			matrix[row][col] = val;
		}
	}

	return *this;
}

//Matrix2 Comparators
bool Matrix2::operator==(const Matrix2& mat) {
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			if (matrix[row][col] != mat.matrix[row][col]) {
				return false;
			}
		}
	}

	return true;
}


bool Matrix2::operator!=(const Matrix2& mat) {
	int count = 0;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			if (matrix[row][col] == mat.matrix[row][col]) {
				count++;
			}
		}
	}
	if (count == 4) {
		return false;
	}
	else {
		return true;
	}
}

//Matrix2 Methods
Matrix2 Matrix2::transposed() { 
	Matrix2 trans;
	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 2; col++) {
			trans.matrix[col][row] = matrix[row][col];
		}
	}

	return trans;
}

Matrix2& Matrix2::transpose() {
	*this = transposed();

	return *this;
}


float Matrix2::determinant() { 
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

	Matrix2 Matrix2::adjoint() { 
		return Matrix2(new float[2][2]{ {matrix[1][1], -matrix[0][1]}, {-matrix[1][0], matrix[0][0]} });

	}

	Matrix2 Matrix2::inverse() { 
		return adjoint() / determinant();
	}

	Matrix2 Matrix2::identity() {
		return Matrix2(new float[2][2]{ {1,0},{0,1} });
	}
