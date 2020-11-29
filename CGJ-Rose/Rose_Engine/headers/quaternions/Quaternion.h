#pragma once
#include "../../headers/vectors/Vector4.h"
#include "../../headers/matrices/Matrix4.h"

class Quaternion
{
private:
	float x, y, z, a;

public: 
	Quaternion();
	Quaternion(float a, float x, float y, float z);
	Quaternion(float theta, Vector4 axis);
	Quaternion(Matrix4 rotationM);

	float getA();
	float getX();
	float getY();
	float getZ();
	void setA(const float a);
	void setX(const float x);
	void setY(const float y);
	void setZ(const float z);

	static Vector4 normalizeVec4(Vector4& v);
	static Quaternion fromAngleAxis(float theta, Vector4& axis);
	void toAngleAxis(float& angle, Vector4& axis);
	void clean();
	float Quadrance();
	float Norm();
	Quaternion Normalize();
	Quaternion Conjugate();
	Quaternion Inverse();
	Quaternion& operator=(const Quaternion& quat);
	bool operator==(const Quaternion& quat);
	Quaternion operator+( const Quaternion& q1);
	Quaternion operator*(const float s);
	Quaternion operator*(const Quaternion& q1);
	Matrix4 GLRotationMatrix();
	Quaternion Lerp(Quaternion& q1, float k);
	Quaternion Slerp(Quaternion& q1, float k);
	friend std::ostream& operator<<(std::ostream& output, Quaternion& q);

};

