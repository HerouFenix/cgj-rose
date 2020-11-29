#include "../../../headers/vectors/Vector2.h"
#include "../../../headers/vectors/Vector3.h"
#include "../../../headers/vectors/Vector4.h"

#include <cassert>

// Vector 2 Constructors
// Vector 2 Constructors
Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
}

Vector2::Vector2(Vector3& vec) {
	x = vec.getX();
	y = vec.getY();
}

Vector2::Vector2(Vector4& vec) {
	x = vec.getX();
	y = vec.getY();
}

//Vector3 Print
std::ostream& operator<<(std::ostream& os, const Vector2& vec)
{
	os << '(' << vec.x << ',' << vec.y << ')';
	return os;
}

//Clone
Vector2 Vector2::clone() {
	return Vector2(x, y);
}

//Vector2 Getters
float Vector2::getX() {
	return x;
}

float Vector2::getY() {
	return y;
}


//Vector2 Setters
void Vector2::setX(float _x) {
	x = _x;
}

void Vector2::setY(float _y) {
	y = _y;
}

void Vector2::set(float _x, float _y) {
	x = _x;
	y = _y;
}

//Vector2 Operations
Vector2 Vector2::operator+(const Vector2& operand)
{
	return Vector2(x + operand.x, y + operand.y);
}

Vector2 Vector2::operator+(float val)
{
	return Vector2(x + val, y + val);
}

Vector2 operator+(float val, Vector2& vec) {
	return Vector2(vec.x + val, vec.y + val);
}

Vector2 Vector2::operator-(const Vector2& operand)
{
	return Vector2(x - operand.x, y - operand.y);
}

Vector2 Vector2::operator-(float val)
{
	return Vector2(x - val, y - val);
}

Vector2 operator-(float val, Vector2& vec) {
	return Vector2(val - vec.x, val - vec.y);
}

Vector2 operator-(Vector2& operand)
{
	return Vector2(-operand.x, -operand.y);
}

Vector2 Vector2::operator*(float operand)
{
	return Vector2(x * operand, y * operand);
}

Vector2 operator*(float val, Vector2& vec) {
	return vec * val;
}


Vector2 Vector2::operator/(float operand)
{
	assert(operand != 0);
	return Vector2(x / operand, y / operand);
}

Vector2 operator/(float val, Vector2& vec) {
	assert(vec.getX() != 0 && vec.getY() != 0);
	return  Vector2(val / vec.getX(), val / vec.getY());
}

//Vector3 Assignments
Vector2& Vector2::operator=(const Vector2& operand)
{
	x = operand.x;
	y = operand.y;
	return *this;
}

Vector2& Vector2::operator+=(const Vector2& operand)
{
	x += operand.x;
	y += operand.y;
	return *this;
}

Vector2& Vector2::operator+=(float val)
{
	x += val;
	y += val;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& operand)
{
	x -= operand.x;
	y -= operand.y;
	return *this;
}

Vector2& Vector2::operator-=(float val)
{
	x -= val;
	y -= val;
	return *this;
}

Vector2& Vector2::operator*=(float operand)
{
	x *= operand;
	y *= operand;
	return *this;
}

Vector2& Vector2::operator/=(float operand)
{
	x /= operand;
	y /= operand;
	return *this;
}

//Vector3 Comparators
bool Vector2::operator==(const Vector2& vec) {
	if (x == vec.x && y == vec.y) {
		return true;
	}
	return false;
}

bool Vector2::operator!=(const Vector2& vec) {
	if (x == vec.x && y == vec.y) {
		return false;
	}
	return true;
}

int Vector2::compareMag(Vector2& vec) {
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

int Vector2::compareMag(float val) {
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

//Vector2 Methods
//Magnitude
float Vector2::magnitude() {
	return sqrt((x * x) + (y * y));
}

//Normalize
Vector2& Vector2::normalize()
{
	float magn = magnitude();
	assert(magn != 0);
	*this /= magn;
	return *this;
}

Vector2 Vector2::normalized()
{
	float magn = magnitude();
	assert(magn != 0);

	return *this / magn;
}

//Dot product
float Vector2::dotProd(const Vector2& operand)
{
	return x * operand.x + operand.y * y;
}

//Perpendicular
Vector2 Vector2::perpendicular()
{
	Vector2 vec(y, -x);

	return vec.normalized();
}

//Quadrance
float Vector2::quadrance()
{
	return x * x + y * y;
}

//Invert
Vector2 Vector2::invert()
{
	*this = -*this;
	return *this;
}

//Distance
float Vector2::dist(const Vector2& vec) {
	return (*this - vec).magnitude();
}

//Angle
float Vector2::angle(Vector2& vec) {
	float cosAngle = dotProd(vec) / (magnitude() * vec.magnitude());
	return acos(cosAngle);
}