#ifndef VECTOR_4
#define VECTOR_4

// Vector4 CLASS HEADER

/// Class used to represent and perform operations with 4-Dimensional vectors

#include<iostream>
#include "../matrices/Matrix4.h"

class Vector2;
class Vector3;

class Vector4 {
	private:
		float x, y, z, w;
	public:
		// FUNCTION DECLARATIONS
	/********************************************/ /**
	 * Creates a new Vector4 object with all coordinates set to 0
	 ***********************************************/
		Vector4();

		/********************************************/ /**
		 * Function used to create a Vector4
		 *
		 * @param _x The x coordinate to be assigned to the new Vector4
		 * @param _y The y coordinate to be assigned to the new Vector4
		 * @param _z The z coordinate to be assigned to the new Vector4
		 * @param _w The w coordinate to be assigned to the new Vector4
		 ***********************************************/
		Vector4(float _x, float _y, float _z, float _w);

		/********************************************/ /**
		* Function used to create a Vector4 from a Vector3
		*
		* @param vec The Vector3 we want to get the coordinates from
		***********************************************/
		Vector4(Vector3& vec);

		/********************************************/ /**
		* Function used to create a Vector4 from a Vector2
		*
		* @param vec The Vector2 we want to get the coordinates from
		***********************************************/
		Vector4(Vector2& vec);

		/********************************************/ /**
		 * Used to create a clone of the vector (that is still a different object)
		 *
		 ***********************************************/
		Vector4 clone();

		/********************************************/ /**
		 * Function used to get the Vector4's x coordinate
		 *
		 * @return x The Vector4's current x coordinate
		 ***********************************************/
		float getX();

		/********************************************/ /**
		 * Function used to get the Vector4's y coordinate
		 *
		 * @return y The Vector4's current y coordinate
		 ***********************************************/
		float getY();

		/********************************************/ /**
		 * Function used to get the Vector4's z coordinate
		 *
		 * @return z The Vector4's current z coordinate
		 ***********************************************/
		float getZ();

		/********************************************/ /**
		 * Function used to get the Vector4's w coordinate
		 *
		 * @return w The Vector4's current w coordinate
		 ***********************************************/
		float getW();

		/********************************************/ /**
		 * Function used to set the Vector4's x coordinate
		 * @param _x The new x coordinate we want to assign to our vector
		 ***********************************************/
		void setX(float _x);

		/********************************************/ /**
		 * Function used to set the Vector4's y coordinate
		 * @param _y The new y coordinate we want to assign to our vector
		 ***********************************************/
		void setY(float _y);

		/********************************************/ /**
		 * Function used to set the Vector4's z coordinate
		 * @param _z The new z coordinate we want to assign to our vector
		 ***********************************************/
		void setZ(float _z);

		/********************************************/ /**
		 * Function used to set the Vector4's w coordinate
		 * @param _w The new w coordinate we want to assign to our vector
		 ***********************************************/
		void setW(float _w);

		/********************************************/ /**
		 * Function used to set the Vector4's coordinates
		 * @param _x The new x coordinate we want to assign to our vector
		 * @param _y The new y coordinate we want to assign to our vector
		 * @param _z The new z coordinate we want to assign to our vector
		 * @param _w The new w coordinate we want to assign to our vector
		 ***********************************************/
		void set(float _x, float _y, float _z, float _w);

		/********************************************/ /**
		 * Overloading of the + operator when summing two Vector4
		 *
		 * @param vec The Vector4 we want to sum with our Vector4
		 * @return vecSum The sum of the two vectors
		 ***********************************************/
		Vector4 operator+(const Vector4& vec);

		/********************************************/ /**
		 * Overloading of the + operator when summing a Vector4 and a scalar
		 *
		 * @param val The scalar we want to sum
		 * @return vecSum The sum of the two vectors
		 ***********************************************/
		Vector4 operator+(float val);

		/********************************************/ /**
		* Overloading of the + operator. Gets the addition of a scalar by our vector
		*
		* @param val The scalar we want to use to sub
		* @return vecSub The resulting subtraction
		***********************************************/
		friend Vector4 operator+(float val, Vector4& vec);

		/********************************************/ /**
		 * Overloading of the += operator. Assigns new coordinates to our vector
		 *
		 * @param vec The Vector4 we want to sum to our Vector4
		 ***********************************************/
		Vector4& operator+=(const Vector4& vec);

		/********************************************/ /**
		 * Overloading of the += operator. Assigns new coordinates to our vector
		 *
		 * @param val The value we want to sum to our Vector4
		 ***********************************************/
		Vector4& operator+=(float val);

		/********************************************/ /**
		 * Overloading of the - operator when subtracting two Vector4
		 *
		 * @param vec The Vector4 we want to subtract with our Vector4
		 * @return vecSub The subtraction of the two vectors
		 ***********************************************/
		Vector4 operator-(const Vector4& vec);

		/********************************************/ /**
		 * Overloading of the - operator when summing a Vector4 and a scalar
		 *
		 * @param val The scalar we want to sub
		 * @return vecSum The sub of a vector and a scalar
		 ***********************************************/
		Vector4 operator-(float val);

		/********************************************/ /**
		* Overloading of the - operator. Gets the subtraction of a scalar by our vector
		*
		* @param val The scalar we want to use to sub
		* @return vecSub The resulting subtraction
		***********************************************/
		friend Vector4 operator-(float val, Vector4& vec);

		/********************************************/ /**
		* Overloading of the - operator. Overloads the -Vector4
		*
		* @param vec The Vector4 we want to subtract with our Vector4
		* @return vecNeg The -Vector4
		***********************************************/
		friend Vector4 operator-(Vector4& vec);

		/********************************************/ /**
		 * Overloading of the -= operator. Assigns new coordinates to our vector
		 *
		 * @param vec The Vector4 we want to sub with our Vector4
		 ***********************************************/
		Vector4& operator-=(const Vector4& vec);

		/********************************************/ /**
		 * Overloading of the -= operator. Assigns new coordinates to our vector
		 *
		 * @param val The value we want to sub to our Vector4
		 ***********************************************/
		Vector4& operator-=(float val);

		/********************************************/ /**
		 * Overloading of the * operator. Gets the multiplication of our vector by a scalar
		 *
		 * @param scal The scalar we want to use to multiply
		 * @return vecMul The resulting multiplication
		 ***********************************************/
		Vector4 operator*(float scalar);

		/********************************************/ /**
		* Overloading of the * operator. Gets the multiplication of a scalar by our vector
		*
		* @param val The scalar we want to use to multiply
		* @return vecMul The resulting multiplication
		***********************************************/
		friend Vector4 operator*(float val, Vector4& vec);

		/********************************************/ /**
		 * Overloading of the *= operator. Assigns new coordinates to our vector
		 *
		 * @param scal The scalar we want to use to multiply
		 * @return vecMul The resulting multiplication
		 ***********************************************/
		Vector4& operator*=(float scalar);

		/********************************************/ /**
		 * Overloading of the / operator. Gets the division of our vector by a scalar
		 *
		 * @param scal The scalar we want to use to divide
		 * @return vecDiv The resulting division
		 ***********************************************/
		Vector4 operator/(float scalar);

		/********************************************/ /**
		* Overloading of the / operator. Gets the division of a scalar by our vector
		*
		* @param val The scalar we want to use to divide
		* @return vecDiv The resulting division
		***********************************************/
		friend Vector4 operator/(float val, Vector4& vec);

		/********************************************/ /**
		 * Overloading of the /= operator. Assigns new coordinates to our vector
		 *
		 * @param scal The scalar we want to use to divide our vector by
		 ***********************************************/
		Vector4& operator/=(float scalar);

		/********************************************/ /**
		 * Overloading of the = operator. Assigns new coordinates to our vector
		 *
		 * @param vec The vector with the coordenates to be copied
		 ***********************************************/
		Vector4& operator=(const Vector4& vec);

		/********************************************/ /**
		 * Overloading of the == operator. Verifies if 2 vectors have the same coordinates
		 *
		 * @param eq True if they have the same coordinates, false otherwise
		 ***********************************************/
		bool operator==(const Vector4& vec);

		/********************************************/ /**
		 * Overloading of the != operator. Verifies if 2 vectors have different coordinates
		 *
		 * @param eq True if they have the different coordinates, false otherwise
		 ***********************************************/
		bool operator!=(const Vector4& vec);

		/********************************************/ /**
		 * Compares the magnitude of two vectors
		 *
		 * @return comp 1 if the vector is bigger than the given one, 0 if they're equal, -1 if smaller
		 ***********************************************/
		int compareMag(Vector4& vec);

		/********************************************/ /**
		 * Compares the magnitude of a vector and a value
		 *
		 * @return comp 1 if the vector is bigger than the given value, 0 if they're equal, -1 if smaller
		 ***********************************************/
		int compareMag(float val);


		/********************************************/ /**
		 * Overloading of the << operator. Prints our vector's coordinates
		 ***********************************************/
		friend std::ostream& operator<<(std::ostream& output, const Vector4& vec);

		/********************************************/ /**
		 * Returns the vector's magnitude
		 *
		 * @return mag The vector's magnitude
		 ***********************************************/
		float magnitude();

		/********************************************/ /**
		 * Returns the Vector normalized. Doesn't change the vector,
		 * just returns its normalized equivalent
		 *
		 * @return norm The normalized equivalent of our vector
		 ***********************************************/
		Vector4 normalized();

		/********************************************/ /**
		 * Normalizes the vector.
		 *
		 ***********************************************/
		Vector4& normalize();

		Vector4 Normalize_Quaternions();

		/********************************************/ /**
		 * Returns the Dot product of two vectors
		 *
		 * @param vec The vector we want to do the Dot product with
		 * @return dot The resulting Dot product of the vectors
		 ***********************************************/
		float dotProd(const Vector4& vec);

		/********************************************/ /**
		 * Returns the Quadrance of a vector
		 *
		 * @return quad The quadrance of the vector
		 ***********************************************/
		float quadrance();

		/********************************************/ /**
		 * Inverts the direction of the vector. Actually modifies it.
		 *
		 ***********************************************/
		Vector4 invert();

		/********************************************/ /**
		 * Distance between two vectors.
		 *
		 * @param vec The vector we want to check the distance with
		 * @return dist The distance between the vectors
		 ***********************************************/
		float dist(const Vector4& vec);


		/********************************************/ /**
		 * Returns the smallest angle between two vectors
		 *
		 * @return ang The shortest angle between this vector and the given one in radians
		 ***********************************************/
		float angle(Vector4& vec);

		Vector4 transform(Matrix4 m);

};



#endif