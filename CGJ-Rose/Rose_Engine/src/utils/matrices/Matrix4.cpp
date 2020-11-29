#include "../../../headers/matrices/Matrix4.h"
#include "../../../headers/matrices/Matrix2.h"
#include "../../../headers/matrices/Matrix3.h"

#include "../../../headers/vectors/Vector3.h"
#include "../../../headers/vectors/Vector4.h"

#include <math.h>
#include <cassert>

# define PI (float)atan(1)*4
# define THRESHOLD (float)1.0e-5

// Matrix 4 Constructors
Matrix4::Matrix4() {
}

Matrix4::Matrix4(float val) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = val;
		}
	}
}

Matrix4::Matrix4(float mat[4][4]) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = mat[row][col];
		}
	}
}

Matrix4::Matrix4(Matrix2& mat) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (row >= 2 || col >= 2) {
				matrix[row][col] = 0;
			}
			else {
				matrix[row][col] = mat[row][col];
			}
		}
	}
}

Matrix4::Matrix4(Matrix3& mat) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (row == 3 || col == 3) {
				matrix[row][col] = 0;
			}
			else {
				matrix[row][col] = mat[row][col];
			}
		}
	}
}

//Matrix4 Print
std::ostream& operator<<(std::ostream& os, const Matrix4& matrix)
{
	os << "\n";
	for (int row = 0; row < 4; row++) {
		os << "[";

		for (int col = 0; col < 4; col++) {
			os << matrix.matrix[row][col];
			if (col != 3) {
				os << ", ";
			}
		}
		os << "]\n";
	}
	return os;
}


//Clone
Matrix4 Matrix4::clone() {
	return Matrix4(matrix);
}

//Matrix4 Getters
float Matrix4::get(int row, int col) {
	assert(row > 0 && row < 4 && col > 0 && col < 4);
	return matrix[row][col];
}


void Matrix4::getRowMajor(float* arr) {
	int index = 0;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			arr[index++] = matrix[row][col];
		}
	}
}

void Matrix4::getColMajor(float* arr) {
	int index = 0;
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			arr[index++] = matrix[row][col];
		}
	}
}

//Matrix4 Setters
void Matrix4::set(int row, int col, float val) {
	assert(row >= 0 && row < 4 && col >= 0 && col < 4);
	matrix[row][col] = val;
}


//Matrix4 Operations
float* Matrix4::operator[](int val) {
	return matrix[val];
}

Matrix4 Matrix4::operator+(const Matrix4& mat)
{
	/* NEEDLESS ASSERTION
	int noRows = sizeof(mat.matrix) / sizeof(mat.matrix[0]);
	int noCols = sizeof(mat.matrix[0]) / sizeof(float);
	std::cout << noRows << "\n";
	assert(noRows == 4 && noCols == 4);
	*/

	Matrix4 matSum;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matSum.matrix[row][col] = matrix[row][col] + mat.matrix[row][col];
		}
	}

	return matSum;
}

Matrix4 Matrix4::operator+(float val)
{
	Matrix4 matSum;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matSum.matrix[row][col] = matrix[row][col] + val;
		}
	}

	return matSum;
}

Matrix4 operator+(float val, Matrix4& mat)
{
	Matrix4 matSum;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matSum.matrix[row][col] = mat.matrix[row][col] + val;
		}
	}

	return matSum;
}

Matrix4 Matrix4::operator-(const Matrix4& mat)
{
	Matrix4 matSub;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matSub.matrix[row][col] = matrix[row][col] - mat.matrix[row][col];
		}
	}

	return matSub;
}

Matrix4 Matrix4::operator-(float val)
{
	Matrix4 matSum;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matSum.matrix[row][col] = matrix[row][col] - val;
		}
	}

	return matSum;
}

Matrix4 operator-(float val, Matrix4& mat)
{
	Matrix4 matSum;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matSum.matrix[row][col] = val-mat.matrix[row][col];
		}
	}

	return matSum;
}

Matrix4 Matrix4::operator*(const Matrix4& mat) {
	Matrix4 matMul;

	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			for (int i = 0; i < 4; ++i)
			{
				matMul.matrix[row][col] += matrix[row][i] * mat.matrix[i][col];
			}
		}
	}

	return matMul;
}

Matrix4 Matrix4::operator*(float val)
{
	Matrix4 matMul;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matMul.matrix[row][col] = matrix[row][col] * val;
		}
	}

	return matMul;
}

Matrix4 operator*(float val, Matrix4& mat)
{
	Matrix4 matMul;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matMul.matrix[row][col] = mat.matrix[row][col] * val;
		}
	}

	return matMul;
}

Vector4 Matrix4::operator*(Vector4& vec) {
	float x = matrix[0][0] * vec.getX() + matrix[0][1] * vec.getY() + matrix[0][2] * vec.getZ() + matrix[0][3] * vec.getW();

	float y = matrix[1][0] * vec.getX() + matrix[1][1] * vec.getY() + matrix[1][2] * vec.getZ() + matrix[1][3] * vec.getW();

	float z = matrix[2][0] * vec.getX() + matrix[2][1] * vec.getY() + matrix[2][2] * vec.getZ() + matrix[2][3] * vec.getW();

	float w = matrix[3][0] * vec.getX() + matrix[3][1] * vec.getY() + matrix[3][2] * vec.getZ() + matrix[3][3] * vec.getW();

	return Vector4(x, y, z, w);
}

Vector4 operator*(Vector4& vec, Matrix4& mat) {
	float x = vec.getX() * mat.matrix[0][0] + vec.getY() * mat.matrix[1][0] + vec.getZ() * mat.matrix[2][0] + vec.getW() * mat.matrix[3][0];

	float y = vec.getX() * mat.matrix[0][1] + vec.getY() * mat.matrix[1][1] + vec.getZ() * mat.matrix[2][1] + vec.getW() * mat.matrix[3][1];

	float z = vec.getX() * mat.matrix[0][2] + vec.getY() * mat.matrix[1][2] + vec.getZ() * mat.matrix[2][2] + vec.getW() * mat.matrix[3][2];

	float w = vec.getX() * mat.matrix[0][3] + vec.getY() * mat.matrix[1][3] + vec.getZ() * mat.matrix[2][3] + vec.getW() * mat.matrix[3][3];

	return Vector4(x, y, z, w);
}

Matrix4 Matrix4::operator/(float val)
{
	Matrix4 matMul;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matMul.matrix[row][col] = matrix[row][col] / val;
		}
	}

	return matMul;
}

Matrix4 operator/(float val, Matrix4& mat)
{
	Matrix4 matMul;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matMul.matrix[row][col] = val / mat.matrix[row][col];
		}
	}

	return matMul;
}

//Matrix4 Assignments
Matrix4& Matrix4::operator+=(const Matrix4& mat) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = matrix[row][col] + mat.matrix[row][col];
		}
	}

	return *this;
}

Matrix4& Matrix4::operator+=(float val) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = matrix[row][col] + val;
		}
	}

	return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4& mat) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = matrix[row][col] - mat.matrix[row][col];
		}
	}

	return *this;
}

Matrix4& Matrix4::operator-=(float val) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = matrix[row][col] - val;
		}
	}

	return *this;
}

Matrix4& Matrix4::operator*=(const Matrix4& mat) {
	return *this = *this * mat;
}

Matrix4& Matrix4::operator*=(float val) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = matrix[row][col] * val;
		}
	}

	return *this;
}

Vector4 operator*=(Vector4& vec, Matrix4& mat) {
	vec.setX(vec.getX() * mat.matrix[0][0] + vec.getY() * mat.matrix[1][0] + vec.getZ() * mat.matrix[2][0] + vec.getW() * mat.matrix[3][0]);

	vec.setY(vec.getX() * mat.matrix[0][1] + vec.getY() * mat.matrix[1][1] + vec.getZ() * mat.matrix[2][1] + vec.getW() * mat.matrix[3][1]);

	vec.setZ(vec.getX() * mat.matrix[0][2] + vec.getY() * mat.matrix[1][2] + vec.getZ() * mat.matrix[2][2] + vec.getW() * mat.matrix[3][2]);

	vec.setW(vec.getW() * mat.matrix[0][3] + vec.getY() * mat.matrix[1][3] + vec.getZ() * mat.matrix[2][3] + vec.getW() * mat.matrix[3][2]);

	return vec;
}

Matrix4& Matrix4::operator/=(float val) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = matrix[row][col] / val;
		}
	}

	return *this;
}

Matrix4& Matrix4::operator=(const Matrix4& mat) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = mat.matrix[row][col];
		}
	}

	return *this;
}

Matrix4& Matrix4::operator=(float val) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			matrix[row][col] = val;
		}
	}

	return *this;
}

//Matrix4 Comparators
bool Matrix4::operator==(const Matrix4& mat) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (abs(matrix[row][col] - mat.matrix[row][col]) > 1e-5) {
				return false;
			}
		}
	}

	return true;
}


bool Matrix4::operator!=(const Matrix4& mat) {
	int count = 0;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (matrix[row][col] == mat.matrix[row][col]) { 
				count++;
			}
		}
	}
	if (count == 16) {
		return false;
	}
	else {
		return true;
	}

}

//Matrix4 Methods
Matrix4 Matrix4::transposed() {
	Matrix4 trans;
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			trans.matrix[col][row] = matrix[row][col];
		}
	}

	return trans;
}

Matrix4& Matrix4::transpose() {

	*this = transposed();

	return *this;
}

Matrix4 Matrix4::identity() {
	return Matrix4(new float[4][4]{ {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} });
}

Matrix4 Matrix4::scaling(float sx, float sy, float sz, float sw) {
	return Matrix4(new float[4][4]{ {sx,0,0,0}, {0,sy,0,0}, {0,0,sz,0}, {0,0,0,sw} });
}

Matrix4 Matrix4::scaling(Vector3& vec) {
	return Matrix4(new float[4][4]{ {vec.getX(),0,0,0}, {0,vec.getY(),0,0}, {0,0,vec.getZ(),0}, {0,0,0,1} });
}

Matrix4 Matrix4::scaling(Vector4& vec) {
	return Matrix4(new float[4][4]{ {vec.getX(),0,0,0}, {0,vec.getY(),0,0}, {0,0,vec.getZ(),0}, {0,0,0,vec.getW()} });
}

Matrix4 Matrix4::translation(float sx, float sy, float sz) {
	return Matrix4(new float[4][4]{ {1,0,0,sx}, {0,1,0,sy}, {0,0,1,sz}, {0,0,0,1} });
}

Matrix4 Matrix4::translation(Vector3& vec) {
	return Matrix4(new float[4][4]{ {1,0,0,vec.getX()}, {0,1,0,vec.getY()}, {0,0,1,vec.getZ()}, {0,0,0,1} });
}

Matrix4 Matrix4::rotation(float sx, float sy, float sz, bool radians, bool round) {
	if (!radians) { // Convert to radians
		sx = sx * PI / 180.0f;
		sy = sy * PI / 180.0f;
		sz = sz * PI / 180.0f;
	}

	float cosG = cos(sx);
	float cosB = cos(sy);
	float cosA = cos(sz);

	float sinG = sin(sx);
	float sinB = sin(sy);
	float sinA = sin(sz);

	// Round - Useful for angles like PI/2 
	if (round) {
		cosG = roundf(cosG * 10000000) / 10000000;
		cosB = roundf(cosB * 10000000) / 10000000;
		cosA = roundf(cosA * 10000000) / 10000000;

		sinG = roundf(sinG * 10000000) / 10000000;
		sinB = roundf(sinB * 10000000) / 10000000;
		sinA = roundf(sinA * 10000000) / 10000000;
	}

	return Matrix4(
		new float[4][4]{ 
			{cosA*cosB, cosA*sinB*sinG - sinA*cosG, cosA*sinB*cosG + sinA*sinG,0}, 
			{sinA*cosB, sinA*sinB*sinG + cosA*cosG, sinA*sinB*cosG - cosA*sinG, 0}, 
			{-sinB, cosB*sinG, cosB*cosG, 0}, 
			{0,0,0,1} 
		}
	);
}

Matrix4 Matrix4::rotation(Vector3& vec, bool radians, bool round) {
	float sx = vec.getX();
	float sy = vec.getY();
	float sz = vec.getZ();
	
	return rotation(sx, sy, sz, radians, round);
}

Matrix4 Matrix4::rotationX(float ang, bool radians, bool round) {
	if (!radians) { // Convert to radians
		ang = ang * PI / 180.0f;
	}

	float cosAng = cos(ang);
	float sinAng = sin(ang);

	// Round - Useful for angles like PI/2 
	if (round) {
		cosAng = roundf(cosAng * 10000000) / 10000000;
		sinAng = roundf(sinAng * 10000000) / 10000000;
	}

	return Matrix4(
		new float[4][4]{
			{1, 0, 0, 0},
			{0, cosAng, -sinAng, 0},
			{0, sinAng, cosAng, 0},
			{0,0,0,1}
		}
	);
}

Matrix4 Matrix4::rotationY(float ang, bool radians, bool round) {
	if (!radians) { // Convert to radians
		ang = ang * PI / 180.0f;
	}

	float cosAng = cos(ang);
	float sinAng = sin(ang);

	// Round - Useful for angles like PI/2 
	if (round) {
		cosAng = roundf(cosAng * 10000000) / 10000000;
		sinAng = roundf(sinAng * 10000000) / 10000000;
	}

	return Matrix4(
		new float[4][4]{
			{cosAng, 0, sinAng, 0},
			{0, 1, 0, 0},
			{-sinAng, 0, cosAng, 0},
			{0,0,0,1}
		}
	);
}

Matrix4 Matrix4::rotationZ(float ang, bool radians, bool round) {
	if (!radians) { // Convert to radians
		ang = ang * PI / 180.0f;
	}
	float cosAng = cos(ang);
	float sinAng = sin(ang);

	// Round - Useful for angles like PI/2 
	if (round) {
		cosAng = roundf(cosAng * 10000000) / 10000000;
		sinAng = roundf(sinAng * 10000000) / 10000000;
	}

	return Matrix4(
		new float[4][4]{
			{cosAng, -sinAng, 0, 0},
			{sinAng, cosAng, 0, 0},
			{0, 0, 1, 0},
			{0,0,0,1}
		}
	);
}

void Matrix4::clean()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (fabs(matrix[i][j]) < THRESHOLD)
				matrix[i][j] = 0.0f;
		}
	}
}

Matrix4 Matrix4::inverse() {
	//
	// Inversion by Cramer's rule.  Code taken from an Intel publication
	//
	double Result[4][4];
	double tmp[12]; /* temp array for pairs */
	double src[16]; /* array of transpose source matrix */
	double det; /* determinant */
	/* transpose matrix */
	for (int i = 0; i < 4; i++)
	{
		src[i + 0] = (*this)[i][0];
		src[i + 4] = (*this)[i][1];
		src[i + 8] = (*this)[i][2];
		src[i + 12] = (*this)[i][3];
	}
	/* calculate pairs for first 8 elements (cofactors) */
	tmp[0] = src[10] * src[15];
	tmp[1] = src[11] * src[14];
	tmp[2] = src[9] * src[15];
	tmp[3] = src[11] * src[13];
	tmp[4] = src[9] * src[14];
	tmp[5] = src[10] * src[13];
	tmp[6] = src[8] * src[15];
	tmp[7] = src[11] * src[12];
	tmp[8] = src[8] * src[14];
	tmp[9] = src[10] * src[12];
	tmp[10] = src[8] * src[13];
	tmp[11] = src[9] * src[12];
	/* calculate first 8 elements (cofactors) */
	Result[0][0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
	Result[0][0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
	Result[0][1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
	Result[0][1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
	Result[0][2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
	Result[0][2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
	Result[0][3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
	Result[0][3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
	Result[1][0] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
	Result[1][0] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
	Result[1][1] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
	Result[1][1] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
	Result[1][2] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
	Result[1][2] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
	Result[1][3] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
	Result[1][3] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
	/* calculate pairs for second 8 elements (cofactors) */
	tmp[0] = src[2] * src[7];
	tmp[1] = src[3] * src[6];
	tmp[2] = src[1] * src[7];
	tmp[3] = src[3] * src[5];
	tmp[4] = src[1] * src[6];
	tmp[5] = src[2] * src[5];

	tmp[6] = src[0] * src[7];
	tmp[7] = src[3] * src[4];
	tmp[8] = src[0] * src[6];
	tmp[9] = src[2] * src[4];
	tmp[10] = src[0] * src[5];
	tmp[11] = src[1] * src[4];
	/* calculate second 8 elements (cofactors) */
	Result[2][0] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
	Result[2][0] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
	Result[2][1] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
	Result[2][1] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
	Result[2][2] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
	Result[2][2] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
	Result[2][3] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
	Result[2][3] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
	Result[3][0] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
	Result[3][0] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
	Result[3][1] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
	Result[3][1] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
	Result[3][2] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
	Result[3][2] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
	Result[3][3] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
	Result[3][3] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
	/* calculate determinant */
	det = src[0] * Result[0][0] + src[1] * Result[0][1] + src[2] * Result[0][2] + src[3] * Result[0][3];
	if (det == 0.0f) {
		return Matrix4();
	}
	/* calculate matrix inverse */
	det = 1.0f / det;

	Matrix4 FloatResult;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			FloatResult[i][j] = float(Result[i][j] * det);
		}
	}
	return FloatResult;
}

Vector3 Matrix4::getTranslation() {
	return Vector3(matrix[0][3], matrix[1][3], matrix[2][3]);
}

Vector3 Matrix4::getScale() {
	return Vector3(
		Vector3(matrix[0][0], matrix[1][0], matrix[2][0]).magnitude(),
		Vector3(matrix[0][1], matrix[1][1], matrix[2][1]).magnitude(),
		Vector3(matrix[0][2], matrix[1][2], matrix[2][2]).magnitude()

	);
}

Matrix4 Matrix4::getRotation() {
	return Matrix4(new float[4][4]
		{
			matrix[0][0] / getScale().getX(), matrix[0][1] / getScale().getY(), matrix[0][2] / getScale().getZ(), 0,
			matrix[1][0] / getScale().getX(), matrix[1][1] / getScale().getY(), matrix[1][2] / getScale().getZ(), 0,
			matrix[2][0] / getScale().getX(), matrix[2][1] / getScale().getY(), matrix[2][2] / getScale().getZ(), 0,
			0, 0, 0, 1
		}
	);
}