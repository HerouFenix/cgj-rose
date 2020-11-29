#ifndef MATRIX_4
#define MATRIX_4

// Matrix4 CLASS HEADER

/// Class used to represent and perform operations with 4x4 Matrices

#include<iostream>

class Vector4;
class Vector3;

class Matrix2;
class Matrix3;

class Matrix4 {
private:
	float matrix[4][4] = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
public:
	// FUNCTION DECLARATIONS
	/********************************************/ /**
	 * Creates a new Matrix4 object with all cells set to 0
	 ***********************************************/
	Matrix4();

	/********************************************/ /**
	 * Creates a new Matrix4 object with the all cells equal to the specified value
	 *
	 * @param val The value of all cells
	 ***********************************************/
	Matrix4(float val);

	/********************************************/ /**
	 * Creates a new Matrix4 object with the cells equal to the specified array of arrays
	 *
	 * @param mat The array of arrays that specify our matrix cell's values
	 ***********************************************/
	Matrix4(float mat[4][4]);

	/********************************************/ /**
	* Function used to create a Matrix4 from a Matrix2
	*
	* @param vec The Matrix4 we want to get the coordinates from
	***********************************************/
	Matrix4(Matrix2& mat);

	/********************************************/ /**
	* Function used to create a Matrix4 from a Matrix3
	*
	* @param vec The Matrix3 we want to get the coordinates from
	***********************************************/
	Matrix4(Matrix3& mat);

	/********************************************/ /**
	 * Overloading of the << operator. Prints our Matrix
	 ***********************************************/
	friend std::ostream& operator<<(std::ostream& output, const Matrix4& vec);

	/********************************************/ /**
	 * Used to create a clone of the matrix (that is still a different object)
	 *
	 ***********************************************/
	Matrix4 clone();

	/********************************************/ /**
	 * Function used to get a specific cell of a Matrix4
	 *
	 * @param row The row of the cell
	 * @param col The column of the cell
	 * @return cel The matrix4 cell at given coordinates
	 ***********************************************/
	float get(int row, int col);

	/********************************************/ /**
	 * Function used to get the matrix in array form
	 *
	 * @return arr The array corresponding to the matrix
	 ***********************************************/
	float* getMatrix();

	/********************************************/ /**
	* Function used to get the matrix in array form (Row Major)
	*
	* @param arr The array corresponding to the matrix
	***********************************************/
	void getRowMajor(float* arr);

	/********************************************/ /**
	* Function used to get the matrix in array form (Col Major)
	*
	* @param arr The array corresponding to the matrix
	***********************************************/
	void getColMajor(float* arr);

	/********************************************/ /**
	 * Function used to set a specific cell's value
	 *
	 * @param row The row of the cell
	 * @param col The column of the cell
	 * @return val The value we want to set the cell to
	 ***********************************************/
	void set(int row, int col, float val);

	/********************************************/ /**
	 * Overloading of the [] operator to get a row
	 *
	 * @param val The row of the matrix
	 ***********************************************/
	float* operator[](int val);

	/********************************************/ /**
	 * Overloading of the + operator when summing two Matrix4
	 *
	 * @param mat The matrix4 we want to sum with
	 * @return matSum The sum of the two matrices
	 ***********************************************/
	Matrix4 operator+(const Matrix4& mat);

	/********************************************/ /**
		* Overloading of the + operator when adding a matrix and a value
		*
		* @param val The value we want to add with
		* @return matSum The sum of a matrix and a val
		***********************************************/
	Matrix4 operator+(float val);

	/********************************************/ /**
	 * Overloading of the + operator when adding a matrix and a value
	 *
	 * @param val The value we want to add with
	 * @return matSum The sum of a matrix and a val
	 ***********************************************/
	friend Matrix4 operator+(float val, Matrix4& mat);

	/********************************************/ /**
	 * Overloading of the - operator when subtracting two Matrix3
	 *
	 * @param mat The matrix3 we want to sub with
	 * @return matSub The sub of the two matrices
	 ***********************************************/
	Matrix4 operator-(const Matrix4& mat);

	/********************************************/ /**
	 * Overloading of the - operator when subtracting a matrix and a value
	 *
	 * @param val The value we want to subtract with
	 * @return matSub The subtraction of the two matrices
	 ***********************************************/
	Matrix4 operator-(float val);

	/********************************************/ /**
	 * Overloading of the - operator when subtracting a matrix and a value
	 *
	 * @param val The value we want to subtract with
	 * @return matSub The subtraction of the two matrices
	 ***********************************************/
	friend Matrix4 operator-(float val, Matrix4& mat);


	/********************************************/ /**
	 * Overloading of the * operator when multiplying two Matrix3
	 *
	 * @param mat The matrix3 we want to multiply with
	 * @return matMult The multiplication of the two matrices
	 ***********************************************/
	Matrix4 operator*(const Matrix4& mat);

	/********************************************/ /**
	 * Overloading of the * operator when multiplying a matrix and a value
	 *
	 * @param val The value we want to multiply with
	 * @return matMult The multiplication of the two matrices
	 ***********************************************/
	Matrix4 operator*(float val);

	/********************************************/ /**
	 * Overloading of the * operator when multiplying a matrix and a value
	 *
	 * @param val The value we want to multiply with
	 * @return matMult The multiplication of the two matrices
	 ***********************************************/
	friend Matrix4 operator*(float val, Matrix4& mat);

	/********************************************/ /**
	 * Overloading of the * operator when multiplying a matrix and a Vector3
	 *
	 * @param vec The vector we want to multiply with
	 * @return Vector3 The multiplication of the two matrices
	 ***********************************************/
	Vector4 operator*(Vector4& vec);

	/********************************************/ /**
	 * Overloading of the * operator when multiplying a Vector and a matrix
	 *
	 * @param val The value we want to multiply with
	 * @return matMult The multiplication of the the vector and the matrix
	 ***********************************************/
	friend Vector4 operator*(Vector4& vec, Matrix4& mat);

	/********************************************/ /**
	 * Overloading of the / operator when dividing a matrix and a value
	 *
	 * @param val The value we want to multiply with
	 * @return matDiv The division of the two matrices
	 ***********************************************/
	Matrix4 operator/(float val);

	/********************************************/ /**
	 * Overloading of the / operator when dividing a matrix and a value
	 *
	 * @param val The value we want to multiply with
	 * @return matDiv The division of the two matrices
	 ***********************************************/
	friend Matrix4 operator/(float val, Matrix4& mat);

	/********************************************/ /**
	 * Overloading of the += operator. Assigns new coordinates to our matrix
	 *
	 * @param mat The Matrix we want to sum to our Matrix
	 ***********************************************/
	Matrix4& operator+=(const Matrix4& vec);

	/********************************************/ /**
	 * Overloading of the += operator. Assigns new coordinates to our matrix
	 *
	 * @param val The value we want to sum by
	 ***********************************************/
	Matrix4& operator+=(float val);

	/********************************************/ /**
	 * Overloading of the -= operator. Assigns new coordinates to our matrix
	 *
	 * @param mat The Matrix we want to sub to our Matrix
	 ***********************************************/
	Matrix4& operator-=(const Matrix4& vec);

	/********************************************/ /**
	 * Overloading of the -= operator. Assigns new coordinates to our matrix
	 *
	 * @param val The value we want to sub by
	 ***********************************************/
	Matrix4& operator-=(float val);

	/********************************************/ /**
	 * Overloading of the *= operator. Assigns new coordinates to our matrix
	 *
	 * @param mat The Matrix we want to multiply to our Matrix
	 ***********************************************/
	Matrix4& operator*=(const Matrix4& vec);

	/********************************************/ /**
	 * Overloading of the *= operator. Assigns new coordinates to our matrix
	 *
	 * @param val The value we want to multiply by
	 ***********************************************/
	Matrix4& operator*=(float val);

	/********************************************/ /**
	 * Overloading of the * operator when multiplying a Vector and a matrix
	 *
	 * @param mat The matrix we want to use to multiply
	 ***********************************************/
	friend Vector4 operator*=(Vector4& vec, Matrix4& mat);

	/********************************************/ /**
	 * Overloading of the /= operator. Assigns new coordinates to our matrix
	 *
	 * @param val The value we want to multiply by
	 ***********************************************/
	Matrix4& operator/=(float val);

	/********************************************/ /**
	 * Overloading of the = operator. Assigns new coordinates to our matrix
	 *
	 * @param mat The matrix with the coordenates to be copied
	 ***********************************************/
	Matrix4& operator=(const Matrix4& vec);

	/********************************************/ /**
	 * Overloading of the = operator. Assigns new coordinates to our matrix
	 *
	 * @param val The value we want our matrix cells to have
	 ***********************************************/
	Matrix4& operator=(float val);

	/********************************************/ /**
	 * Overloading of the == operator. Verifies if 2 matrices have the same coordinates
	 *
	 * @return eq True if they have the same cells, false otherwise
	 ***********************************************/
	bool operator==(const Matrix4& mat);

	/********************************************/ /**
	 * Overloading of the != operator. Verifies if 2 matrices have different coordinates
	 *
	 * @return eq True if they have the different coordinates, false otherwise
	 ***********************************************/
	bool operator!=(const Matrix4& mat);

	/********************************************/ /**
	 * Returns the matrix transposed
	 *
	 * @return mat The transposed equivalent of the matrix
	 ***********************************************/
	Matrix4 transposed();

	/********************************************/ /**
	 * Converts matrix to its transposed
	 *
	 * @return The converted matrix
	 ***********************************************/
	Matrix4& transpose();

	/********************************************/ /**
	 * Returns the identity matrix
	 *
	 * @return mat The 4x4 identity matrix
	 ***********************************************/
	static Matrix4 identity();

	/********************************************/ /**
	 * Returns the scaling matrix according to the given parameters
	 *
	 * @param sx The x value to use on the scaling
	 * @param sy The y value to use on the scaling
	 * @param sz The z value to use on the scaling
	 * @param sw The w value to use on the scaling
	 * @return mat The 4x4 scaling matrix
	 ***********************************************/
	static Matrix4 scaling(float sx, float sy, float sz, float sw = 1);

	/********************************************/ /**
	 * Returns the scaling matrix according to the given parameters
	 *
	 * @param vec The parameters to use on the scaling
	 * @return mat The 4x4 scaling matrix
	 ***********************************************/
	static Matrix4 scaling(Vector3& vec);

	/********************************************/ /**
	 * Returns the scaling matrix according to the given parameters
	 *
	 * @param vec The parameters to use on the scaling
	 * @return mat The 4x4 scaling matrix
	 ***********************************************/
	static Matrix4 scaling(Vector4& vec);

	/********************************************/ /**
	 * Returns the rotation matrix according to the given parameters
	 *
	 * @param sx The x value to use on the rotation
	 * @param sy The y value to use on the rotation
	 * @param sz The z value to use on the rotation
	 * @param sw The w value to use on the rotation
	 * @param radians Whether you're using radians or not. Default is true
	 * @param round Whether the cos and sin values should be rounded out to 8 decimal places
	 * @return mat The 4x4 rotation matrix
	 ***********************************************/
	static Matrix4 rotation(float sx, float sy, float sz, bool radians=true, bool round = false);

	/********************************************/ /**
	 * Returns the rotation matrix according to the given parameters
	 *
	 * @param radians Whether you're using radians or not. Default is true
	 * @param vec The parameters to use on the rotation
	 * @param round Whether the cos and sin values should be rounded out to 8 decimal places
	 * @return mat The 4x4 rotation matrix
	 ***********************************************/
	static Matrix4 rotation(Vector3& vec, bool radians=true, bool round = false);

	/********************************************/ /**
	 * Returns the rotation matrix over the X axis
	 *
	 * @param ang The angle of rotation
	 * @param radians Whether you're using radians or not. Default is true
	 * @param round Whether the cos and sin values should be rounded out to 8 decimal places
	 * @return mat The 4x4 rotation matrix
	 ***********************************************/
	static Matrix4 rotationX(float ang, bool radians = true, bool round = false);

	/********************************************/ /**
	 * Returns the rotation matrix over the Y axis
	 *
	 * @param ang The angle of rotation
	 * @param radians Whether you're using radians or not. Default is true
	 * @param round Whether the cos and sin values should be rounded out to 8 decimal places
	 * @return mat The 4x4 rotation matrix
	 ***********************************************/
	static Matrix4 rotationY(float ang, bool radians = true, bool round = false);

	/********************************************/ /**
	 * Returns the rotation matrix over the Z axis
	 *
	 * @param ang The angle of rotation
	 * @param radians Whether you're using radians or not. Default is true
	 * @param round Whether the cos and sin values should be rounded out to 8 decimal places
	 * @return mat The 4x4 rotation matrix
	 ***********************************************/
	static Matrix4 rotationZ(float ang, bool radians = true, bool round = false);


	/********************************************/ /**
	 * Returns the translation matrix according to the given parameters
	 *
	 * @param sx The x value to use on the translation
	 * @param sy The y value to use on the translation
	 * @param sz The z value to use on the translation
	 * @param sw The w value to use on the translation
	 * @return mat The 4x4 translation matrix
	 ***********************************************/
	static Matrix4 translation(float sx, float sy, float sz);

	/********************************************/ /**
	 * Returns the translation matrix according to the given parameters
	 *
	 * @param vec The parameters to use on the translation
	 * @return mat The 4x4 translation matrix
	 ***********************************************/
	static Matrix4 translation(Vector3& vec);

	void clean();

	Matrix4 inverse();

	Vector3 getTranslation();

	Vector3 getScale();

	Matrix4 getRotation();
};



#endif