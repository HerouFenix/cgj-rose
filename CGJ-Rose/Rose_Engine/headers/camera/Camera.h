#pragma once
#include "../matrices/Matrix4.h"
#include "../vectors/Vector3.h"
#include "../../../CGJ-Engine/dependencies/glew/include/GL/glew.h"
#include "../quaternions/Quaternion.h"

// CAMERA CLASS HEADER

/// Class used to represent and control an FPS-Like Free-3D camera

class Camera
{
private:
	Vector3 cameraEye; // The camera position is a vector in world space that points to the camera's position.
	Vector3 cameraCenter; // The camera's target (i.e what it is looking at)
	Vector3 cameraUp; // The up vector that points upwards (in world space)

	Vector3 initialEye;
	Vector3 initialCenter;
	Vector3 initialUp;

	Vector3 cameraDirection; // What constitutes as "moving forward"
	float pitch = 0;
	float yaw = 0;

	Matrix4 view;
	Matrix4 orthoProj;
	Matrix4 perspProj;

public:
	// FUNCTION DECLARATIONS

	/********************************************/ /**
	 * Creates a new Camera at position eye, pointing to target at center and with an up direction of up
	 * @param eye - The position of the camera
	 * @param center - The position of the camera's target (what its looking at)
	 * @param up - The vector that defines what constitutes as "up"
	 ***********************************************/
	Camera(Vector3 eye, Vector3 center, Vector3 up);

	/********************************************/ /**
	 * Destroys the Camera object
	 ***********************************************/
	~Camera();

	/********************************************/ /**
	 * Used to set the view matrix of the Camera, effectively altering it.
	 * @param eye - The position of the camera
	 * @param center - The position of the camera's target (what its looking at)
	 * @param up - The vector that defines what constitutes as "up"
	 ***********************************************/
	void setViewMatrix(Vector3 eye, Vector3 center, Vector3 up);

	/********************************************/ /**
	 * Defines an orthographic projection matrix associated with this camera
	 * @param left - The leftmost coordinate
	 * @param right - The rightmost coordinate
	 * @param bottom - The bottom-most coordinate
	 * @param top - The top-most coordinate
	 * @param near - The nearest coordinate
	 * @param far - The furthest coordinate
	 ***********************************************/
	void setOrthoProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);

	/********************************************/ /**
	 * Defines a Perspective Projection matrix associated with this camera
	 * @param fovy - The Y axis Field of View
	 * @param aspect - The aspect ratio (should be the Window's width divided by the height)
	 * @param nearZ - The nearest coordinate
	 * @param farZ - The furthest coordinate
	 ***********************************************/
	void setPrespProjectionMatrix(GLfloat fovy, GLfloat aspect, GLfloat nearZ, GLfloat farZ);

	/********************************************/ /**
	 * Changes the camera's direction, i.e, where it is looking at.
	 * @param xOffset - How much to move the camera's direction left/right
	 * @param yOffset - How much to move the camera's direction up/down
	 ***********************************************/
	void setDirection(float xOffset, float yOffset);


	/********************************************/ /**
	 * Returns the Orthogonal View-Projection matrix (Projection * View)
	 * @return The matrix resulting from the multiplication of the Orthogonal Projection matrix and the View matrix
	 ***********************************************/
	const Matrix4 getOrthVP();

	/********************************************/ /**
	 * Returns the Perspective View-Projection matrix (Projection * View)
	 * @return The matrix resulting from the multiplication of the Perspective Projection matrix and the View matrix
	 ***********************************************/
	const Matrix4 getPerspVP();

	/********************************************/ /**
	 * Returns the Orthogonal Projection Matrix
	 * @return The currently set orthogonal projection matrix
	 ***********************************************/
	const Matrix4 getOrthProj();

	/********************************************/ /**
	 * Returns the Perspective Projection Matrix
	 * @return The currently set perspective projection matrix
	 ***********************************************/
	const Matrix4 getPerspProj();

	/********************************************/ /**
	 * Returns the View Matrix
	 * @return The currently set view matrix
	 ***********************************************/
	const Matrix4 getViewMatrix();

	/********************************************/ /**
	 * Moves the camera in the specified direction with the specified speed. Does this by altering the view matrix
	 * @param move - The type of movement. 0-Forward, 1-Backward, 2-Left, 3-Right
	 * @param speed - How much we want to move the camera. Default is 0.1
	 ***********************************************/
	void moveCamera(int move, float speed = 0.1f);

	/********************************************/ /**
	 * Moves the camera forward with the specified speed. Does this by altering the view matrix
	 * @param speed - How much we want to move the camera. Default is 0.1
	 ***********************************************/
	void moveCameraForward(float speed = 0.1f);

	/********************************************/ /**
	 * Moves the camera backward with the specified speed. Does this by altering the view matrix
	 * @param speed - How much we want to move the camera. Default is 0.1
	 ***********************************************/
	void moveCameraBackward(float speed = 0.1f);

	/********************************************/ /**
	 * Moves the camera left with the specified speed. Does this by altering the view matrix
	 * @param speed - How much we want to move the camera. Default is 0.1
	 ***********************************************/
	void moveCameraLeft(float speed = 0.1f);

	/********************************************/ /**
	 * Moves the camera right with the specified speed. Does this by altering the view matrix
	 * @param speed - How much we want to move the camera. Default is 0.1
	 ***********************************************/
	void moveCameraRight(float speed = 0.1f);

	/********************************************/ /**
	 * Moves the camera upward with the specified speed. Does this by altering the view matrix
	 * @param speed - How much we want to move the camera. Default is 0.1
	 ***********************************************/
	void moveCameraUp(float speed = 0.1f);

	/********************************************/ /**
	 * Moves the camera downard with the specified speed. Does this by altering the view matrix
	 * @param speed - How much we want to move the camera. Default is 0.1
	 ***********************************************/
	void moveCameraDown(float speed = 0.1f);


	/********************************************/ /**
	 * Rotates the camera.
	 * @param xOffset - How much we want to move the camera from left to right
	 * @param xOffset - How much we want to move the camera from down to up
	 * @param sensitivity - How much we want to rotate the camera
	 ***********************************************/
	void rotateCamera(float xOffset, float yOffset, float sensitivity = 0.1f);

	/********************************************/ /**
	 * Rotates the camera around a point
	 ***********************************************/
	void rotateCameraAround(Vector3 point = Vector3(0,0,0));

	/********************************************/ /**
	 * Rotates the camera around a point
	 ***********************************************/
	void rotateCameraAround(float rotationDegree, Vector3 point = Vector3(0, 0, 0));

	/********************************************/ /**
	 * Rotates the camera around a point using quaternions
	 ***********************************************/
	void rotateCameraAroundQuaternion(float rotationDegree, Vector3 point = Vector3(0, 0, 0));

	/********************************************/ /**
	 * Inverts the camera by inverting the signs of all of the eye's coordinates
	 ***********************************************/
	void invertCamera();

	/********************************************/ /**
	 * Resets the camera to the values set when constructing the object
	 ***********************************************/
	void resetCamera();
};