#ifndef MATRIX_3
#define MATRIX_3

// Matrix3 CLASS HEADER

/// Class used to represent and perform operations with 3x3 Matrices

#include<iostream>

class Vector3;
class Matrix2;
class Matrix4;

class Matrix3 {
	private:
		float matrix[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} };
	public:
		// FUNCTION DECLARATIONS
		/********************************************/ /**
		 * Creates a new Matrix3 object with all cells set to 0
		 ***********************************************/
		Matrix3();

		/********************************************/ /**
		 * Creates a new Matrix3 object with the all cells equal to the specified value
		 *
		 * @param val The value of all cells
		 ***********************************************/
		Matrix3(float val);

		/********************************************/ /**
		 * Creates a new Matrix3 object with the cells equal to the specified array of arrays
		 * 
		 * @param mat The array of arrays that specify our matrix cell's values
		 ***********************************************/
		Matrix3(float mat[3][3]);

		/********************************************/ /**
		* Function used to create a Matrix3 from a Matrix2
		*
		* @param vec The Matrix2 we want to get the coordinates from
		***********************************************/
		Matrix3(Matrix2& mat);

		/********************************************/ /**
		* Function used to create a Matrix3 from a Matrix4
		*
		* @param vec The Matrix4 we want to get the coordinates from
		***********************************************/
		Matrix3(Matrix4& mat);

		/********************************************/ /**
		 * Overloading of the << operator. Prints our Matrix
		 ***********************************************/
		friend std::ostream& operator<<(std::ostream& output, const Matrix3& vec);

		/********************************************/ /**
		 * Used to create a clone of the matrix (that is still a different object)
		 *
		 ***********************************************/
		Matrix3 clone();

		/********************************************/ /**
		 * Function used to get a specific cell of a Matrix3
		 *
		 * @param row The row of the cell
		 * @param col The column of the cell
		 * @return cel The matrix3 cell at given coordinates
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
		 * Overloading of the + operator when summing two Matrix3
		 *
		 * @param mat The matrix3 we want to sum with
		 * @return matSum The sum of the two matrices
		 ***********************************************/
		Matrix3 operator+(const Matrix3& mat);

		/********************************************/ /**
		* Overloading of the + operator when adding a matrix and a value
		*
		* @param val The value we want to add with
		* @return matSum The sum of a matrix and a val
		***********************************************/
		Matrix3 operator+(float val);

		/********************************************/ /**
		 * Overloading of the + operator when adding a matrix and a value
		 *
		 * @param val The value we want to add with
		 * @return matSum The sum of a matrix and a val
		 ***********************************************/
		friend Matrix3 operator+(float val, Matrix3& mat);

		/********************************************/ /**
		 * Overloading of the - operator when subtracting two Matrix3
		 *
		 * @param mat The matrix3 we want to sub with
		 * @return matSub The sub of the two matrices
		 ***********************************************/
		Matrix3 operator-(const Matrix3& mat);

		/********************************************/ /**
		 * Overloading of the - operator when subtracting a matrix and a value
		 *
		 * @param val The value we want to subtract with
		 * @return matSub The subtraction of the two matrices
		 ***********************************************/
		Matrix3 operator-(float val);

		/********************************************/ /**
		 * Overloading of the - operator when subtracting a matrix and a value
		 *
		 * @param val The value we want to subtract with
		 * @return matSub The subtraction of the two matrices
		 ***********************************************/
		friend Matrix3 operator-(float val, Matrix3& mat);


		/********************************************/ /**
		 * Overloading of the * operator when multiplying two Matrix3
		 *
		 * @param mat The matrix3 we want to multiply with
		 * @return matMult The multiplication of the two matrices
		 ***********************************************/
		Matrix3 operator*(const Matrix3& mat);

		/********************************************/ /**
		 * Overloading of the * operator when multiplying a matrix and a value
		 *
		 * @param val The value we want to multiply with
		 * @return matMult The multiplication of the two matrices
		 ***********************************************/
		Matrix3 operator*(float val);

		/********************************************/ /**
		 * Overloading of the * operator when multiplying a matrix and a value
		 *
		 * @param val The value we want to multiply with
		 * @return matMult The multiplication of the two matrices
		 ***********************************************/
		friend Matrix3 operator*(float val, Matrix3& mat);

		/********************************************/ /**
		 * Overloading of the * operator when multiplying a matrix and a Vector3
		 *
		 * @param vec The vector we want to multiply with
		 * @return Vector3 The multiplication of the two matrices
		 ***********************************************/
		Vector3 operator*(Vector3& vec);

		/********************************************/ /**
		 * Overloading of the * operator when multiplying a Vector and a matrix
		 *
		 * @param val The value we want to multiply with
		 * @return matMult The multiplication of the the vector and the matrix
		 ***********************************************/
		friend Vector3 operator*(Vector3& vec, Matrix3& mat);

		/********************************************/ /**
		 * Overloading of the / operator when dividing a matrix and a value
		 *
		 * @param val The value we want to multiply with
		 * @return matDiv The division of the two matrices
		 ***********************************************/
		Matrix3 operator/(float val);

		/********************************************/ /**
		 * Overloading of the / operator when dividing a matrix and a value
		 *
		 * @param val The value we want to multiply with
		 * @return matDiv The division of the two matrices
		 ***********************************************/
		friend Matrix3 operator/(float val, Matrix3& mat);

		/********************************************/ /**
		 * Overloading of the += operator. Assigns new coordinates to our matrix
		 *
		 * @param mat The Matrix we want to sum to our Matrix
		 ***********************************************/
		Matrix3& operator+=(const Matrix3& vec);

		/********************************************/ /**
		 * Overloading of the += operator. Assigns new coordinates to our matrix
		 *
		 * @param val The value we want to sum by
		 ***********************************************/
		Matrix3& operator+=(float val);

		/********************************************/ /**
		 * Overloading of the -= operator. Assigns new coordinates to our matrix
		 *
		 * @param mat The Matrix we want to sub to our Matrix
		 ***********************************************/
		Matrix3& operator-=(const Matrix3& vec);

		/********************************************/ /**
		 * Overloading of the -= operator. Assigns new coordinates to our matrix
		 *
		 * @param val The value we want to sub by
		 ***********************************************/
		Matrix3& operator-=(float val);

		/********************************************/ /**
		 * Overloading of the *= operator. Assigns new coordinates to our matrix
		 *
		 * @param mat The Matrix we want to multiply to our Matrix
		 ***********************************************/
		Matrix3& operator*=(const Matrix3& vec);

		/********************************************/ /**
		 * Overloading of the *= operator. Assigns new coordinates to our matrix
		 *
		 * @param val The value we want to multiply by
		 ***********************************************/
		Matrix3& operator*=(float val);

		/********************************************/ /**
		 * Overloading of the * operator when multiplying a Vector and a matrix
		 *
		 * @param mat The matrix we want to use to multiply
		 ***********************************************/
		friend Vector3 operator*=(Vector3& vec, Matrix3& mat);

		/********************************************/ /**
		 * Overloading of the /= operator. Assigns new coordinates to our matrix
		 *
		 * @param val The value we want to multiply by
		 ***********************************************/
		Matrix3& operator/=(float val);

		/********************************************/ /**
		 * Overloading of the = operator. Assigns new coordinates to our matrix
		 *
		 * @param mat The matrix with the coordenates to be copied
		 ***********************************************/
		Matrix3& operator=(const Matrix3& vec);

		/********************************************/ /**
		 * Overloading of the = operator. Assigns new coordinates to our matrix
		 *
		 * @param val The value we want our matrix cells to have
		 ***********************************************/
		Matrix3& operator=(float val);

		/********************************************/ /**
		 * Overloading of the == operator. Verifies if 2 matrices have the same coordinates
		 *
		 * @return eq True if they have the same cells, false otherwise
		 ***********************************************/
		bool operator==(const Matrix3& mat);

		/********************************************/ /**
		 * Overloading of the != operator. Verifies if 2 matrices have different coordinates
		 *
		 * @return eq True if they have the different coordinates, false otherwise
		 ***********************************************/
		bool operator!=(const Matrix3& mat);

		/********************************************/ /**
		 * Returns the matrix transposed
		 *
		 * @return mat The transposed equivalent of the matrix
		 ***********************************************/
		Matrix3 transposed();

		/********************************************/ /**
		* Converts matrix to its transposed
		*
		* @return The converted matrix
		***********************************************/
		Matrix3& transpose();

		/********************************************/ /**
		 * Returns the matrix's determinant
		 *
		 * @return det The determinant of the matrix
		 ***********************************************/
		float determinant();

		/********************************************/ /**
		 * Returns the adjoint matrix
		 *
		 * @return adj The adjoint of the matrix
		 ***********************************************/
		Matrix3 adjoint();

		/********************************************/ /**
		 * Returns the inverse matrix or throws an error if the matrix can't be inversed
		 *
		 * @return mat The inversed matrix
		 ***********************************************/
		Matrix3 inverse();

		/********************************************/ /**
		 * Returns the identity matrix
		 *
		 * @return mat The 3x3 identity matrix
		 ***********************************************/
		static Matrix3 identity();

		/********************************************/ /**
		 * Returns the dual matrix according to the given vector
		 *
		 * @param vec The vector to build the dual matrix with
		 * @return mat The 3x3 dual matrix
		 ***********************************************/
		static Matrix3 dual(Vector3& vec);
};



#endif