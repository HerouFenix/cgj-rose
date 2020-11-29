#ifndef VECTOR_3
#define VECTOR_3

// Vector3 CLASS HEADER

/// Class used to represent and perform operations with 3-Dimensional vectors

#include<iostream>

class Vector2;
class Vector4;

class Vector3 {
	private:
		float x, y, z;
	public:
		// FUNCTION DECLARATIONS
		/********************************************/ /**
		 * Creates a new Vector3 object with all coordinates set to 0
		 ***********************************************/
		Vector3();

		/********************************************/ /**
		 * Function used to create a Vector3
		 *
		 * @param _x The x coordinate to be assigned to the new Vector3
		 * @param _y The y coordinate to be assigned to the new Vector3
		 * @param _z The z coordinate to be assigned to the new Vector3
		 ***********************************************/
		Vector3(float _x, float _y, float _z);

		/********************************************/ /**
		 * Function used to create a Vector3 from a Vector2
		 *
		 * @param vec The Vector2 we want to get the coordinates from
		 ***********************************************/
		Vector3(Vector2& vec);

		/********************************************/ /**
		 * Function used to create a Vector3 from a Vector4
		 *
		 * @param vec The Vector2 we want to get the coordinates from
		 ***********************************************/
		Vector3(Vector4& vec);

		/********************************************/ /**
		 * Used to create a clone of the vector (that is still a different object)
		 *
		 ***********************************************/
		Vector3 clone();

		/********************************************/ /**
		 * Function used to get the Vector3's x coordinate
		 *
		 * @return x The Vector3's current x coordinate
		 ***********************************************/
		float getX();

		/********************************************/ /**
		 * Function used to get the Vector3's y coordinate
		 *
		 * @return y The Vector3's current y coordinate
		 ***********************************************/
		float getY();

		/********************************************/ /**
		 * Function used to get the Vector3's z coordinate
		 *
		 * @return z The Vector3's current z coordinate
		 ***********************************************/
		float getZ();

		/********************************************/ /**
		 * Function used to set the Vector3's x coordinate
		 * @param _x The new x coordinate we want to assign to our vector
		 ***********************************************/
		void setX(float _x);

		/********************************************/ /**
		 * Function used to set the Vector3's y coordinate
		 * @param _y The new x coordinate we want to assign to our vector
		 ***********************************************/
		void setY(float _y);

		/********************************************/ /**
		 * Function used to set the Vector3's z coordinate
		 * @param _z The new x coordinate we want to assign to our vector
		 ***********************************************/
		void setZ(float _z);

		/********************************************/ /**
		 * Function used to set the Vector3's coordinate
		 * @param _x The new x coordinate we want to assign to our vector
		 * @param _y The new y coordinate we want to assign to our vector
		 * @param _z The new z coordinate we want to assign to our vector
		 ***********************************************/
		void set(float _x, float _y, float _z);

		/********************************************/ /**
		 * Overloading of the + operator when summing two Vector3
		 *
		 * @param vec The Vector3 we want to sum with our Vector3
		 * @return vecSum The sum of the two vectors
		 ***********************************************/
		Vector3 operator+(const Vector3& vec);

		/********************************************/ /**
		* Overloading of the + operator when summing a Vector3 and a scalar
		*
		* @param val The scalar we want to sum
		* @return vecSum The sum of the two vectors
		***********************************************/
		Vector3 operator+(float val);

		/********************************************/ /**
		* Overloading of the + operator. Gets the addition of a scalar by our vector
		*
		* @param val The scalar we want to use to sub
		* @return vecSub The resulting subtraction
		***********************************************/
		friend Vector3 operator+(float val, Vector3& vec);

		/********************************************/ /**
		 * Overloading of the += operator. Assigns new coordinates to our vector
		 *
		 * @param vec The Vector3 we want to sum to our Vector3
		 ***********************************************/
		Vector3& operator+=(const Vector3& vec);

		/********************************************/ /**
		* Overloading of the += operator. Assigns new coordinates to our vector
		*
		* @param val The value we want to sum to our Vector3
		***********************************************/
		Vector3& operator+=(float val);

		/********************************************/ /**
		 * Overloading of the - operator when subtracting two Vector3
		 *
		 * @param vec The Vector3 we want to subtract with our Vector3
		 * @return vecSub The subtraction of the two vectors
		 ***********************************************/
		Vector3 operator-(const Vector3& vec);

		/********************************************/ /**
		* Overloading of the - operator when summing a Vector3 and a scalar
		*
		* @param val The scalar we want to sub
		* @return vecSum The sub of a vector and a scalar
		***********************************************/
		Vector3 operator-(float val);

		/********************************************/ /**
		* Overloading of the - operator. Gets the subtraction of a scalar by our vector
		*
		* @param val The scalar we want to use to sub
		* @return vecSub The resulting subtraction
		***********************************************/
		friend Vector3 operator-(float val, Vector3& vec);

		/********************************************/ /**
		 * Overloading of the - operator. Overloads the -Vector3
		 *
		 * @param vec The Vector3 we want to subtract with our Vector3
		 * @return vecNeg The -Vector3
		 ***********************************************/
		friend Vector3 operator-(Vector3& vec);

		/********************************************/ /**
		 * Overloading of the -= operator. Assigns new coordinates to our vector
		 *
		 * @param vec The Vector3 we want to sub with our Vector3
		 ***********************************************/
		Vector3& operator-=(const Vector3& vec);

		/********************************************/ /**
		* Overloading of the -= operator. Assigns new coordinates to our vector
		*
		* @param val The value we want to sub to our Vector3
		***********************************************/
		Vector3& operator-=(float val);

		/********************************************/ /**
		 * Overloading of the * operator. Gets the multiplication of our vector by a scalar
		 *
		 * @param scal The scalar we want to use to multiply
		 * @return vecMul The resulting multiplication
		 ***********************************************/
		Vector3 operator*(float scalar);

		/********************************************/ /**
		 * Overloading of the * operator. Gets the multiplication of our vector by a vector
		 *
		 * @param scal The scalar we want to use to multiply
		 * @return vecMul The resulting multiplication
		 ***********************************************/
		Vector3 operator*(Vector3 vec);

		/********************************************/ /**
		 * Overloading of the * operator. Gets the multiplication of a scalar by our vector
		 *
		 * @param val The scalar we want to use to multiply
		 * @return vecMul The resulting multiplication
		 ***********************************************/
		friend Vector3 operator*(float val, Vector3& vec);

		/********************************************/ /**
		 * Overloading of the *= operator. Assigns new coordinates to our vector
		 *
		 * @param scal The scalar we want to use to multiply
		 * @return vecMul The resulting multiplication
		 ***********************************************/
		Vector3& operator*=(float scalar);

		/********************************************/ /**
		 * Overloading of the / operator. Gets the division of our vector by a scalar
		 *
		 * @param scal The scalar we want to use to divide
		 * @return vecDiv The resulting division
		 ***********************************************/
		Vector3 operator/(float scalar);

		/********************************************/ /**
		* Overloading of the / operator. Gets the division of a scalar by our vector
		*
		* @param val The scalar we want to use to divide
		* @return vecDiv The resulting division
		***********************************************/
		friend Vector3 operator/(float val, Vector3& vec);

		/********************************************/ /**
		 * Overloading of the /= operator. Assigns new coordinates to our vector
		 *
		 * @param scal The scalar we want to use to divide our vector by
		 ***********************************************/
		Vector3& operator/=(float scalar);

		/********************************************/ /**
		 * Overloading of the = operator. Assigns new coordinates to our vector
		 *
		 * @param vec The vector with the coordenates to be copied
		 ***********************************************/
		Vector3& operator=(const Vector3& vec);

		/********************************************/ /**
		 * Overloading of the == operator. Verifies if 2 vectors have the same coordinates
		 *
		 * @param eq True if they have the same coordinates, false otherwise
		 ***********************************************/
		bool operator==(const Vector3& vec);

		/********************************************/ /**
		 * Overloading of the != operator. Verifies if 2 vectors have different coordinates
		 *
		 * @param eq True if they have the different coordinates, false otherwise
		 ***********************************************/
		bool operator!=(const Vector3& vec);

		/********************************************/ /**
		 * Compares the magnitude of two vectors
		 *
		 * @return comp 1 if the vector is bigger than the given one, 0 if they're equal, -1 if smaller
		 ***********************************************/
		int compareMag(Vector3& vec);

		/********************************************/ /**
		 * Compares the magnitude of a vector and a value
		 *
		 * @return comp 1 if the vector is bigger than the given value, 0 if they're equal, -1 if smaller
		 ***********************************************/
		int compareMag(float val);


		/********************************************/ /**
		 * Overloading of the << operator. Prints our vector's coordinates
		 ***********************************************/
		friend std::ostream& operator<<(std::ostream& output, const Vector3& vec);

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
		Vector3 normalized();

		/********************************************/ /**
		 * Normalizes the vector.
		 *
		 ***********************************************/
		Vector3& normalize();

		/********************************************/ /**
		 * Returns the Dot product of two vectors
		 *
		 * @param vec The vector we want to do the Dot product with
		 * @return dot The resulting Dot product of the vectors
		 ***********************************************/
		float dotProd(const Vector3& vec);

		/********************************************/ /**
		 * Returns the Cross product of two vectors
		 *
		 * @param vec The vector we want to do the Cross product with
		 * @return dot The resulting Cross product of the vectors
		 ***********************************************/
		Vector3 crossProd(const Vector3& vec);

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
		Vector3 invert();

		/********************************************/ /**
		 * Distance between two vectors.
		 *
		 * @param vec The vector we want to check the distance with
		 * @return dist The distance between the vectors
		 ***********************************************/
		float dist(const Vector3& vec);


		/********************************************/ /**
		 * Returns the smallest angle between two vectors
		 *
		 * @return ang The shortest angle between this vector and the given one in radians
		 ***********************************************/
		float angle(Vector3& vec);

		Vector3 Lerp(Vector3 finalPos, float by);

};



#endif