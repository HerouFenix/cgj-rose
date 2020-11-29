#include "../../../headers/camera/Camera.h"
# define PI (float)atan(1)*4
#include <GLFW/glfw3.h>

Camera::Camera(Vector3 eye, Vector3 center, Vector3 up)
{
	cameraDirection = (center - eye).normalize();

	// Set initial pitch and yaw

	// cameraDirection.Y = sinPitch => pitch = aSin(cameraDirection.Y)
	pitch = asin(cameraDirection.getY());

	// cameraDirection.X = cosYaw * cosPitch => cosYaw = cameraDirection.X/cosPitch => Yaw = aCos(cameraDirection.X/cosPitch)
	yaw = acos(cameraDirection.getX() / cos(pitch));

	if (eye.getZ() < 0 && yaw > 0) {
		yaw = -yaw;
	}

	initialEye = eye;
	initialCenter = center;
	initialUp = up;

	setViewMatrix(eye, eye + cameraDirection, up);
}

Camera::~Camera()
{
}


void Camera::setViewMatrix(Vector3 eye, Vector3 center, Vector3 up)
{
	cameraEye = eye;
	cameraCenter = center;
	cameraUp = up;

	Vector3 v = (center - eye).normalize(); // CameraDirection

	Vector3 s = v.crossProd(up).normalize(); // CameraRight

	Vector3 u = s.crossProd(v); // CameraUp

	Matrix4 axis(new float[4][4]{
			{  s.getX(),  s.getY(),	 s.getZ(), 0},
			{  u.getX(),  u.getY(),	 u.getZ(), 0},
			{ -v.getX(), -v.getY(), -v.getZ(), 0},
			{ 0,         0,		    0,        1}
		});

	Matrix4 trans(new float[4][4]{
			{ 1, 0, 0, -eye.getX()},
			{ 0, 1, 0, -eye.getY()},
			{ 0, 0, 1, -eye.getZ()},
			{ 0, 0, 0,	1		  }
		});

	view = axis * trans;
}

void Camera::setOrthoProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
{
	orthoProj = Matrix4(new float[4][4]{
		{2 / (right - left), 0                 , 0               , (left + right) / (left - right)},
		{0                 , 2 / (top - bottom), 0               , (bottom + top) / (bottom - top)},
		{0                 , 0                 , 2 / (near - far), (near + far) / (near - far)},
		{0                 , 0                 , 0               , 1},
		}
	);
}

void Camera::setPrespProjectionMatrix(GLfloat fovy, GLfloat aspect, GLfloat nearZ, GLfloat farZ)
{
	GLfloat ang_rad = (fovy / 2.0f) * PI / 180.0f;
	GLfloat d = 1 / tan(ang_rad);

	perspProj = Matrix4(new float[4][4]{
			{(d / aspect), 0,  0                                , 0                                  },
			{0           , d,  0                                , 0                                  },
			{0           , 0,  ((nearZ + farZ) / (nearZ - farZ)), 2 * (nearZ * farZ) / (nearZ - farZ)},
			{0           , 0, -1                                , 0                                  }
		}
	);
}

void Camera::setDirection(float xOffset, float yOffset)
{
	// Convert degrees to radians
	xOffset = xOffset * PI / 180.0f;
	yOffset = yOffset * PI / 180.0f;

	yaw -= xOffset;
	pitch += yOffset;

	float cosYaw = cos(yaw);
	float cosPitch = cos(pitch);
	float sinPitch = sin(pitch);
	float sinYaw = sin(yaw);

	cameraDirection.setX(cosYaw * cosPitch);
	cameraDirection.setY(sinPitch);
	cameraDirection.setZ(-sinYaw * cosPitch);

	cameraDirection.normalize();
}


const Matrix4 Camera::getViewMatrix() {
	return view;
}

const Matrix4 Camera::getOrthProj() {
	return orthoProj;
}

const Matrix4 Camera::getPerspProj() {
	return perspProj;
}

const Matrix4 Camera::getOrthVP()
{
	return orthoProj * view;
}

const Matrix4 Camera::getPerspVP()
{
	return perspProj * view;
}


void Camera::moveCamera(int move, float speed)
{

	switch (move) {
	case 0:
		cameraEye += speed * cameraDirection;
		break;
	case 1:
		cameraEye -= speed * cameraDirection;
		break;
	case 2:
		cameraEye -= cameraDirection.crossProd(cameraUp).normalize() * speed;
		break;
	case 3:
		cameraEye += cameraDirection.crossProd(cameraUp).normalize() * speed;
		break;
	}

	setViewMatrix(cameraEye, cameraEye + cameraDirection, cameraUp);
}

void Camera::moveCameraForward(float speed) {
	cameraEye += speed * cameraDirection;
	setViewMatrix(cameraEye, cameraEye + cameraDirection, cameraUp);
}

void Camera::moveCameraBackward(float speed) {
	cameraEye -= speed * cameraDirection;
	setViewMatrix(cameraEye, cameraEye + cameraDirection, cameraUp);
}

void Camera::moveCameraLeft(float speed) {
	cameraEye -= cameraDirection.crossProd(cameraUp).normalize() * speed;
	setViewMatrix(cameraEye, cameraEye + cameraDirection, cameraUp);
}

void Camera::moveCameraRight(float speed) {
	cameraEye += cameraDirection.crossProd(cameraUp).normalize() * speed;
	setViewMatrix(cameraEye, cameraEye + cameraDirection, cameraUp);
}

void Camera::moveCameraUp(float speed) {
	cameraEye += speed * cameraUp;
	setViewMatrix(cameraEye, cameraEye + cameraDirection, cameraUp);
}

void Camera::moveCameraDown(float speed) {
	cameraEye -= speed * cameraUp;
	setViewMatrix(cameraEye, cameraEye + cameraDirection, cameraUp);
}

void Camera::rotateCamera(float xOffset, float yOffset, float sensitivity)
{
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	setDirection(xOffset, yOffset);
	setViewMatrix(cameraEye, cameraEye + cameraDirection, cameraUp);

}

void Camera::rotateCameraAround(Vector3 point)
{
	float camX = sin(glfwGetTime()) * 5 + point.getX();
	float camZ = cos(glfwGetTime()) * 5 + point.getZ();

	cameraEye.setX(camX);
	cameraEye.setZ(camZ);

	// Set direction to look at point
	cameraDirection = (point - cameraEye).normalize();


	// cameraDirection.Y = sinPitch => pitch = aSin(cameraDirection.Y)
	pitch = asin(cameraDirection.getY());

	// cameraDirection.X = cosYaw * cosPitch => cosYaw = cameraDirection.X/cosPitch => Yaw = aCos(cameraDirection.X/cosPitch)
	yaw = acos(cameraDirection.getX() / cos(pitch));

	if (cameraEye.getZ() < 0 && yaw > 0) {
		yaw = -yaw;
	}
	

	setViewMatrix(cameraEye, cameraEye + cameraDirection, cameraUp);
}

void Camera::rotateCameraAround(float rotationDegree, Vector3 point)
{
	float rotationRads = rotationDegree * PI / 180.0f;

	Vector3 neg = -point;
	Vector4 standIn = cameraEye;
	standIn = Matrix4::translation(neg) * standIn;
	standIn = Matrix4::rotationY(rotationRads) * standIn;
	standIn = Matrix4::translation(point) * standIn;

	cameraEye = standIn;

	// Set direction to look at point
	cameraDirection = (point - cameraEye).normalize();


	// cameraDirection.Y = sinPitch => pitch = aSin(cameraDirection.Y)
	pitch = asin(cameraDirection.getY());

	// cameraDirection.X = cosYaw * cosPitch => cosYaw = cameraDirection.X/cosPitch => Yaw = aCos(cameraDirection.X/cosPitch)
	yaw = acos(cameraDirection.getX() / cos(pitch));

	if (cameraEye.getZ() < 0 && yaw > 0) {
		yaw = -yaw;
	}


	setViewMatrix(cameraEye, cameraEye + cameraDirection, cameraUp);
}

void Camera::rotateCameraAroundQuaternion(float rotationDegree, Vector3 point)
{
	float thetai = 45.0f;
	Vector4 axis_i = { 0.0f, 1.0f, 0.0f, 1.0f };
	Quaternion qtr(rotationDegree, axis_i);

	Vector4 vec4(cameraEye.getX(), cameraEye.getY(), cameraEye.getZ(), 1.0f);
	Vector4 rot = qtr.GLRotationMatrix() * vec4;
	Vector3 eye_rot(rot.getX(), rot.getY(), rot.getZ());

	cameraEye = eye_rot;

	// Set direction to look at point
	cameraDirection = (point - cameraEye).normalize();


	// cameraDirection.Y = sinPitch => pitch = aSin(cameraDirection.Y)
	pitch = asin(cameraDirection.getY());

	// cameraDirection.X = cosYaw * cosPitch => cosYaw = cameraDirection.X/cosPitch => Yaw = aCos(cameraDirection.X/cosPitch)
	yaw = acos(cameraDirection.getX() / cos(pitch));

	if (cameraEye.getZ() < 0 && yaw > 0) {
		yaw = -yaw;
	}

	setViewMatrix(cameraEye, cameraEye + cameraDirection, cameraUp);
}

void Camera::invertCamera()
{
	cameraEye = -cameraEye;

	cameraDirection = -cameraDirection;

	// Set initial pitch and yaw

	// cameraDirection.Y = sinPitch => pitch = aSin(cameraDirection.Y)
	pitch = asin(cameraDirection.getY());

	// cameraDirection.X = cosYaw * cosPitch => cosYaw = cameraDirection.X/cosPitch => Yaw = aCos(cameraDirection.X/cosPitch)
	yaw = acos(cameraDirection.getX() / cos(pitch));

	if (cameraEye.getZ() < 0 && yaw > 0) {
		yaw = -yaw;
	}

	setViewMatrix(cameraEye, cameraEye + cameraDirection, cameraUp);
}

void Camera::resetCamera()
{
	cameraDirection = (initialCenter - initialEye).normalize();

	// Set initial pitch and yaw

	// cameraDirection.Y = sinPitch => pitch = aSin(cameraDirection.Y)
	pitch = asin(cameraDirection.getY());

	// cameraDirection.X = cosYaw * cosPitch => cosYaw = cameraDirection.X/cosPitch => Yaw = aCos(cameraDirection.X/cosPitch)
	yaw = acos(cameraDirection.getX() / cos(pitch));

	if (initialEye.getZ() < 0 && yaw > 0) {
		yaw = -yaw;
	}

	setViewMatrix(initialEye, initialEye + cameraDirection, initialUp);
}

