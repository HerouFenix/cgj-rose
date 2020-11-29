#include "../../headers/vectors/Vector2.h"
#include "../../headers/vectors/Vector3.h"
#include "../../headers/vectors/Vector4.h"

#include <cassert>

// Vector 3 Constructors
Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

Vector3::Vector3(Vector2& vec) {
	x = vec.getX();
	y = vec.getY();
	z = 0;
}

Vector3::Vector3(Vector4& vec) {
	x = vec.getX();
	y = vec.getY();
	z = vec.getZ();
}

//Vector3 Print
std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
	os << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')';
	return os;
}

//Clone
Vector3 Vector3::clone() {
	return Vector3(x, y, z);
}

//Vector3 Getters
float Vector3::getX() {
	return x;
}

float Vector3::getY() {
	return y;
}

float Vector3::getZ() {
	return z;
}

//Vector3 Setters
void Vector3::setX(float _x) {
	x = _x;
}

void Vector3::setY(float _y) {
	y = _y;
}

void Vector3::setZ(float _z) {
	z = _z;
}

void Vector3::set(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

//Vector3 Operations
Vector3 Vector3::operator+(const Vector3& operand)
{
	return Vector3(x + operand.x, y + operand.y, z + operand.z);
}

Vector3 Vector3::operator+(float val)
{
	return Vector3(x + val, y + val, z + val);
}

Vector3 operator+(float val, Vector3& vec) {
	return Vector3(vec.x + val, vec.y + val, vec.z + val);
}

Vector3 Vector3::operator-(const Vector3& operand)
{
	return Vector3(x - operand.x, y - operand.y, z - operand.z);
}


Vector3 Vector3::operator-(float val)
{
	return Vector3(x - val, y - val, z - val);
}

Vector3 operator-(float val, Vector3& vec) {
	return Vector3(val - vec.x, val - vec.y, val - vec.z);
}

Vector3 operator-(Vector3& operand)
{
	return Vector3(-operand.x, -operand.y, -operand.z);
}

Vector3 Vector3::operator*(float operand)
{
	return Vector3(x * operand, y * operand, z * operand);
}

Vector3 Vector3::operator*(Vector3 vec)
{

	return Vector3(x * vec.getX(), y * vec.getY(), z * vec.getZ());
}

Vector3 operator*(float val, Vector3& vec) {
	return vec * val;
}


Vector3 Vector3::operator/(float operand)
{
	assert(operand != 0);
	return Vector3(x / operand, y / operand, z / operand);
}

Vector3 operator/(float val, Vector3& vec) {
	assert(vec.getX() != 0 && vec.getY() != 0 && vec.getZ() != 0);
	return  Vector3(val / vec.getX(), val / vec.getY(), val / vec.getZ());
}


//Vector3 Assignments
Vector3& Vector3::operator=(const Vector3& operand)
{
	x = operand.x;
	y = operand.y;
	z = operand.z;
	return *this;
}

Vector3& Vector3::operator+=(const Vector3& operand)
{
	x += operand.x;
	y += operand.y;
	z += operand.z;
	return *this;
}

Vector3& Vector3::operator+=(float val)
{
	x += val;
	y += val;
	z += val;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& operand)
{
	x -= operand.x;
	y -= operand.y;
	z -= operand.z;
	return *this;
}

Vector3& Vector3::operator-=(float val)
{
	x -= val;
	y -= val;
	z -= val;
	return *this;
}

Vector3& Vector3::operator*=(float operand)
{
	x *= operand;
	y *= operand;
	z *= operand;
	return *this;
}

Vector3& Vector3::operator/=(float operand)
{
	x /= operand;
	y /= operand;
	z /= operand;
	return *this;
}

//Vector3 Comparators
bool Vector3::operator==(const Vector3& vec) {
	if (x == vec.x && y == vec.y && z == vec.z) {
		return true;
	}
	return false;
}

bool Vector3::operator!=(const Vector3& vec) {
	if (x == vec.x && y == vec.y && z == vec.z) {
		return false;
	}
	return true;
}

int Vector3::compareMag(Vector3& vec) {
	float thisMagn = magnitude();
	float otherMagn = vec.magnitude();

	if (thisMagn > otherMagn) {
		return 1;
	}
	else if (thisMagn < otherMagn) {
		return -1;
	}
	else {
		return 0;
	}
}

int Vector3::compareMag(float val) {
	float thisMagn = magnitude();

	if (thisMagn > val) {
		return 1;
	}
	else if (thisMagn < val) {
		return -1;
	}
	else {
		return 0;
	}
}

//Vector3 Methods
//Magnitude
float Vector3::magnitude() {
	return sqrt((x * x) + (y * y) + (z * z));
}

//Normalize
Vector3& Vector3::normalize()
{
	float magn = magnitude();
	assert(magn != 0);
	*this /= magn;
	return *this;
}

Vector3 Vector3::normalized()
{
	float magn = magnitude();
	assert(magn != 0);

	return *this / magn;
}

//Dot product
float Vector3::dotProd(const Vector3& operand)
{
	return x * operand.x + operand.y * y + operand.z * z;
}

//Cross product
Vector3 Vector3::crossProd(const Vector3& operand)
{
	return Vector3(y * operand.z - z * operand.y,
		z * operand.x - x * operand.z, x * operand.y - y * operand.x);
}

//Quadrance
float Vector3::quadrance()
{
	return x * x + y * y + z * z;
}

//Invert
Vector3 Vector3::invert()
{
	*this = -*this;
	return *this;
}

//Distance
float Vector3::dist(const Vector3& vec) {
	return (*this - vec).magnitude();
}

//Angle
float Vector3::angle(Vector3& vec) {
	float cosAngle = dotProd(vec) / (magnitude() * vec.magnitude());
	return acos(cosAngle);
}

//Lerp
Vector3 Vector3::Lerp(Vector3 finalPos, float by)
{
	float retX = x + by * (finalPos.getX() - x);
	float retY = y + by * (finalPos.getY() - y);
	float retZ = z + by * (finalPos.getZ() - z);
	return Vector3(retX, retY, retZ);
}

