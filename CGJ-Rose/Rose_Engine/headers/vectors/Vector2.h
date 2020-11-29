#ifndef VECTOR_2
#define VECTOR_2

// Vector2 CLASS HEADER

/// Class used to represent and perform operations with 4-Dimensional vectors

#include<iostream>

class Vector3;
class Vector4;

class Vector2 {
private:
	float x, y;
public:
	// FUNCTION DECLARATIONS
	/********************************************/ /**
	 * Creates a new Vector2 object with all coordinates set to 0
	 ***********************************************/
	Vector2();

	/********************************************/ /**
	 * Function used to create a Vector2
	 *
	 * @param _x The x coordinate to be assigned to the new Vector2
	 * @param _y The y coordinate to be assigned to the new Vector2
	 ***********************************************/
	Vector2(float _x, float _y);

	/********************************************/ /**
	* Function used to create a Vector2 from a Vector3
	*
	* @param vec The Vector2 we want to get the coordinates from
	***********************************************/
	Vector2(Vector3& vec);

	/********************************************/ /**
	* Function used to create a Vector2 from a Vector4
	*
	* @param vec The Vector2 we want to get the coordinates from
	***********************************************/
	Vector2(Vector4& vec);

	/********************************************/ /**
	 * Used to create a clone of the vector (that is still a different object)
	 *
	 ***********************************************/
	Vector2 clone();

	/********************************************/ /**
	 * Function used to get the Vector2's x coordinate
	 *
	 * @return x The Vector2's current x coordinate
	 ***********************************************/
	float getX();

	/********************************************/ /**
	 * Function used to get the Vector2's y coordinate
	 *
	 * @return y The Vector2's current y coordinate
	 ***********************************************/
	float getY();

	/********************************************/ /**
	 * Function used to set the Vector2's x coordinate
	 * @param _x The new x coordinate we want to assign to our vector
	 ***********************************************/
	void setX(float _x);

	/********************************************/ /**
	 * Function used to set the Vector2's y coordinate
	 * @param _y The new x coordinate we want to assign to our vector
	 ***********************************************/
	void setY(float _y);

	/********************************************/ /**
	 * Function used to set the Vector2's x and y coordinates
	 * @param _x The new x coordinate we want to assign to our vector
	 * @param _y The new x coordinate we want to assign to our vector
	 ***********************************************/
	void set(float _x, float _y);

	/********************************************/ /**
	 * Overloading of the + operator when summing two Vector2
	 *
	 * @param vec The Vector2 we want to sum with our Vector2
	 * @return vecSum The sum of the two vectors
	 ***********************************************/
	Vector2 operator+(const Vector2& vec);

	/********************************************/ /**
	* Overloading of the + operator when summing a Vector2 and a scalar
	*
	* @param val The scalar we want to sum
	* @return vecSum The sum of the two vectors
	***********************************************/
	Vector2 operator+(float val);

	/********************************************/ /**
	* Overloading of the + operator. Gets the addition of a scalar by our vector
	*
	* @param val The scalar we want to use to sub
	* @return vecSub The resulting subtraction
	***********************************************/
	friend Vector2 operator+(float val, Vector2& vec);

	/********************************************/ /**
	 * Overloading of the += operator. Assigns new coordinates to our vector
	 *
	 * @param vec The Vector2 we want to sum to our Vector2
	 ***********************************************/
	Vector2& operator+=(const Vector2& vec);

	/********************************************/ /**
	* Overloading of the += operator. Assigns new coordinates to our vector
	*
	* @param val The value we want to sum to our Vector2
	***********************************************/
	Vector2& operator+=(float val);

	/********************************************/ /**
	 * Overloading of the - operator when subtracting two Vector2
	 *
	 * @param vec The Vector2 we want to subtract with our Vector2
	 * @return vecSub The subtraction of the two vectors
	 ***********************************************/
	Vector2 operator-(const Vector2& vec);

	/********************************************/ /**
	* Overloading of the - operator when summing a Vector2 and a scalar
	*
	* @param val The scalar we want to sub
	* @return vecSum The sub of a vector and a scalar
	***********************************************/
	Vector2 operator-(float val);

	/********************************************/ /**
	* Overloading of the - operator. Gets the subtraction of a scalar by our vector
	*
	* @param val The scalar we want to use to sub
	* @return vecSub The resulting subtraction
	***********************************************/
	friend Vector2 operator-(float val, Vector2& vec);

	/********************************************/ /**
	* Overloading of the - operator. Overloads the -Vector2
	*
	* @param vec The Vector2 we want to subtract with our Vector2
	* @return vecNeg The -Vector2
	***********************************************/
	friend Vector2 operator-(Vector2& vec);

	/********************************************/ /**
	 * Overloading of the -= operator. Assigns new coordinates to our vector
	 *
	 * @param vec The Vector2 we want to sub with our Vector2
	 ***********************************************/
	Vector2& operator-=(const Vector2& vec);

	/********************************************/ /**
	* Overloading of the -= operator. Assigns new coordinates to our vector
	*
	* @param val The value we want to sub to our Vector2
	***********************************************/
	Vector2& operator-=(float val);

	/********************************************/ /**
	 * Overloading of the * operator. Gets the multiplication of our vector by a scalar
	 *
	 * @param scal The scalar we want to use to multiply
	 * @return vecMul The resulting multiplication
	 ***********************************************/
	Vector2 operator*(float scalar);

	/********************************************/ /**
	* Overloading of the * operator. Gets the multiplication of a scalar by our vector
	*
	* @param val The scalar we want to use to multiply
	* @return vecMul The resulting multiplication
	***********************************************/
	friend Vector2 operator*(float val, Vector2& vec);

	/********************************************/ /**
	 * Overloading of the *= operator. Assigns new coordinates to our vector
	 *
	 * @param scal The scalar we want to use to multiply
	 * @return vecMul The resulting multiplication
	 ***********************************************/
	Vector2& operator*=(float scalar);

	/********************************************/ /**
	 * Overloading of the / operator. Gets the division of our vector by a scalar
	 *
	 * @param scal The scalar we want to use to divide
	 * @return vecDiv The resulting division
	 ***********************************************/
	Vector2 operator/(float scalar);

	/********************************************/ /**
	* Overloading of the / operator. Gets the division of a scalar by our vector
	*
	* @param val The scalar we want to use to divide
	* @return vecDiv The resulting division
	***********************************************/
	friend Vector2 operator/(float val, Vector2& vec);

	/********************************************/ /**
	 * Overloading of the /= operator. Assigns new coordinates to our vector
	 *
	 * @param scal The scalar we want to use to divide our vector by
	 ***********************************************/
	Vector2& operator/=(float scalar);

	/********************************************/ /**
	 * Overloading of the = operator. Assigns new coordinates to our vector
	 *
	 * @param vec The vector with the coordenates to be copied
	 ***********************************************/
	Vector2& operator=(const Vector2& vec);

	/********************************************/ /**
	 * Overloading of the == operator. Verifies if 2 vectors have the same coordinates
	 *
	 * @param eq True if they have the same coordinates, false otherwise
	 ***********************************************/
	bool operator==(const Vector2& vec);

	/********************************************/ /**
	 * Overloading of the != operator. Verifies if 2 vectors have different coordinates
	 *
	 * @param eq True if they have the different coordinates, false otherwise
	 ***********************************************/
	bool operator!=(const Vector2& vec);

	/********************************************/ /**
	 * Compares the magnitude of two vectors
	 *
	 * @return comp 1 if the vector is bigger than the given one, 0 if they're equal, -1 if smaller
	 ***********************************************/
	int compareMag(Vector2& vec);

	/********************************************/ /**
	 * Compares the magnitude of a vector and a value
	 *
	 * @return comp 1 if the vector is bigger than the given value, 0 if they're equal, -1 if smaller
	 ***********************************************/
	int compareMag(float val);


	/********************************************/ /**
	 * Overloading of the << operator. Prints our vector's coordinates
	 ***********************************************/
	friend std::ostream& operator<<(std::ostream& output, const Vector2& vec);

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
	Vector2 normalized();

	/********************************************/ /**
	 * Normalizes the vector.
	 *
	 ***********************************************/
	Vector2& normalize();

	/********************************************/ /**
	 * Returns the Dot product of two vectors
	 *
	 * @param vec The vector we want to do the Dot product with
	 * @return dot The resulting Dot product of the vectors
	 ***********************************************/
	float dotProd(const Vector2& vec);

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
	Vector2 invert();

	/********************************************/ /**
	 * Distance between two vectors.
	 *
	 * @param vec The vector we want to check the distance with
	 * @return dist The distance between the vectors
	 ***********************************************/
	float dist(const Vector2& vec);

	/********************************************/ /**
	 * Returns a unit vector perpendicular to this one (clock-wise rotation)
	 *
	 * @return perp The perpendicular vector
	 ***********************************************/
	Vector2 perpendicular();

	/********************************************/ /**
	 * Returns the smallest angle between two vectors
	 *
	 * @return ang The shortest angle between this vector and the given one
	 ***********************************************/
	float angle(Vector2& vec);
};



#endif