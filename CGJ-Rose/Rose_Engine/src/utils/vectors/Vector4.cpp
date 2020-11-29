#include "../../../headers/vectors/Vector2.h"
#include "../../../headers/vectors/Vector3.h"
#include "../../../headers/vectors/Vector4.h"

#include <cassert>

#define THRESHOLD (float)1.0e-5

// Vector 4 Constructors
Vector4::Vector4() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4::Vector4(float _x, float _y, float _z, float _w) {
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Vector4::Vector4(Vector2& vec) {
	x = vec.getX();
	y = vec.getY();
	z = 0;
	w = 0;
}

Vector4::Vector4(Vector3& vec) {
	x = vec.getX();
	y = vec.getY();
	z = vec.getZ();
	w = 0;
}

//Vector4 Print
std::ostream& operator<<(std::ostream& os, const Vector4& vec)
{
	os << '(' << vec.x << ',' << vec.y << ',' << vec.z << ',' << vec.w << ')';
	return os;
}

//Clone
Vector4 Vector4::clone() {
	return Vector4(x, y, z, w);
}

//Vector4 Getters
float Vector4::getX() {
	return x;
}

float Vector4::getY() {
	return y;
}

float Vector4::getZ() {
	return z;
}

float Vector4::getW() {
	return w;
}

//Vector4 Setters
void Vector4::setX(float _x) {
	x = _x;
}

void Vector4::setY(float _y) {
	y = _y;
}

void Vector4::setZ(float _z) {
	z = _z;
}

void Vector4::setW(float _w) {
	w = _w;
}

void Vector4::set(float _x, float _y, float _z, float _w) {
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

//Vector4 Operations
Vector4 Vector4::operator+(const Vector4& operand)
{
	return Vector4(x + operand.x, y + operand.y, z + operand.z, w + operand.w);
}

Vector4 Vector4::operator+(float val)
{
	return Vector4(x + val, y + val, z + val, w + val);
}

Vector4 operator+(float val, Vector4& vec) {
	return Vector4(vec.x + val, vec.y + val, vec.z + val, vec.w + val);
}

Vector4 Vector4::operator-(const Vector4& operand)
{
	return Vector4(x - operand.x, y - operand.y, z - operand.z, w - operand.w);
}

Vector4 Vector4::operator-(float val)
{
	return Vector4(x - val, y - val, z - val, w - val);
}

Vector4 operator-(float val, Vector4& vec) {
	return Vector4(val - vec.x, val - vec.y, val - vec.z, val - vec.w);
}

Vector4 operator-(Vector4& operand)
{
	return Vector4(-operand.x, -operand.y, -operand.z, -operand.w);
}

Vector4 Vector4::operator*(float operand)
{
	return Vector4(x * operand, y * operand, z * operand, w * operand);
}

Vector4 operator*(float val, Vector4& vec) {
	return vec * val;
}


Vector4 Vector4::operator/(float operand)
{
	assert(operand != 0);
	return Vector4(x / operand, y / operand, z / operand, w / operand);
}

Vector4 operator/(float val, Vector4& vec) {
	assert(vec.getX() != 0 && vec.getY() != 0 && vec.getZ() != 0 && vec.getW() != 0);
	return  Vector4(val / vec.getX(), val / vec.getY(), val / vec.getZ(), val / vec.getW());
}


//Vector4 Assignments
Vector4& Vector4::operator=(const Vector4& operand)
{
	x = operand.x;
	y = operand.y;
	z = operand.z;
	w = operand.w;
	return *this;
}

Vector4& Vector4::operator+=(const Vector4& operand)
{
	x += operand.x;
	y += operand.y;
	z += operand.z;
	w += operand.w;
	return *this;
}

Vector4& Vector4::operator+=(float val)
{
	x += val;
	y += val;
	z += val;
	w += val;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& operand)
{
	x -= operand.x;
	y -= operand.y;
	z -= operand.z;
	w -= operand.w;
	return *this;
}

Vector4& Vector4::operator-=(float val)
{
	x -= val;
	y -= val;
	z -= val;
	w -= val;
	return *this;
}

Vector4& Vector4::operator*=(float operand)
{
	x *= operand;
	y *= operand;
	z *= operand;
	w *= operand;
	return *this;
}

Vector4& Vector4::operator/=(float operand)
{
	x /= operand;
	y /= operand;
	z /= operand;
	w /= operand;
	return *this;
}

//Vector4 Comparators
bool Vector4::operator==(const Vector4& v1) {
	return (fabs(x - v1.x) < THRESHOLD && fabs(y - v1.y) < THRESHOLD &&
		fabs(z - v1.z) < THRESHOLD && fabs(w - v1.w) < THRESHOLD);
}

bool Vector4::operator!=(const Vector4& vec) {
	if (x == vec.x && y == vec.y && z == vec.z && w == vec.w) {
		return false;
	}
	return true;
}

int Vector4::compareMag(Vector4& vec) {
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

int Vector4::compareMag(float val) {
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

//Vector4 Methods
//Magnitude
float Vector4::magnitude() {
	return sqrt((x * x) + (y * y) + (z * z) + (w * w));
}

//Normalize
Vector4& Vector4::normalize()
{
	float magn = magnitude();
	assert(magn != 0);
	*this /= magn;
	return *this;
}

Vector4 Vector4::Normalize_Quaternions()
{
	Vector4 vn;
	float s = 1 / (w * sqrt(x * x + y * y + z * z));
	vn.x = x * s;
	vn.y = y * s;
	vn.z = z * s;
	vn.w = 1.0f;
	return vn;
}

Vector4 Vector4::normalized()
{
	float magn = magnitude();
	assert(magn != 0);

	return *this / magn;
}

//Dot product
float Vector4::dotProd(const Vector4& operand)
{
	return x * operand.x + operand.y * y + operand.z * z + operand.w * w;
}

//Quadrance
float Vector4::quadrance()
{
	return x * x + y * y + z * z + w * w;
}

//Invert
Vector4 Vector4::invert()
{
	*this = -*this;
	return *this;
}

//Distance
float Vector4::dist(const Vector4& vec) {
	return (*this - vec).magnitude();
}

//Angle
float Vector4::angle(Vector4& vec) {
	float cosAngle = dotProd(vec) / (magnitude() * vec.magnitude());
	return acos(cosAngle);
}

Vector4 Vector4::transform(Matrix4 m)
{
	Vector4 result;

	result.setX((m[0][0] * x) + (m[0][1] * y) + (m[0][2] * z) + (m[0][3] * w));
	result.setY((m[1][0] * x) + (m[1][1] * y) + (m[1][2] * z) + (m[1][3] * w));
	result.setZ((m[2][0] * x) + (m[2][1] * y) + (m[2][2] * z) + (m[2][3] * w));
	result.setW((m[3][0] * x) + (m[3][1] * y) + (m[3][2] * z) + (m[3][3] * w));

	return result;
}

