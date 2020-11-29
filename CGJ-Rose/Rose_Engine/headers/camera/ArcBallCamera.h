#pragma once
#include "../matrices/Matrix4.h"
#include "../vectors/Vector3.h"
#include "../../../CGJ-Engine/dependencies/glew/include/GL/glew.h"
#include "../quaternions/Quaternion.h"

// ARC BALL CAMERA CLASS HEADER

/// Class used to represent and control an Arc-Ball camera

class ArcBallCamera
{
private:
	float radius;
	float initialRadius;

	Matrix4 rotation;
	Matrix4 translation;

	Matrix4 orthoProj;
	Matrix4 perspProj;

	GLuint vbo_id;
	GLuint UBO_BP;

public:
	// FUNCTION DECLARATIONS

	ArcBallCamera(float radius);

	ArcBallCamera();

	/********************************************/ /**
	 * Destroys the Camera object
	 ***********************************************/
	~ArcBallCamera();


	void SetupCamera(GLuint UBO_BP_);

	void RenderCamera(bool ortho);

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
	 * Change the camera radius
	 ***********************************************/
	void incrementRadius(float inc);

	/********************************************/ /**
	 * Rotates the camera around a point
	 ***********************************************/
	void rotateCameraAroundHorizontal(float rotationDegree);

	/********************************************/ /**
	 * Rotates the camera around a point using quaternions
	 ***********************************************/
	void rotateCameraAroundQuaternionHorizontal(float rotationDegree);

	/********************************************/ /**
	 * Rotates the camera around a point
	 ***********************************************/
	void rotateCameraAroundVertical(float rotationDegree);

	/********************************************/ /**
	 * Rotates the camera around a point using quaternions
	 ***********************************************/
	void rotateCameraAroundQuaternionVertical(float rotationDegree);

	/********************************************/ /**
	 * Rotates the camera around a point
	 ***********************************************/
	void rotateCameraAroundZ(float rotationDegree);

	/********************************************/ /**
	 * Rotates the camera around a point using quaternions
	 ***********************************************/
	void rotateCameraAroundQuaternionZ(float rotationDegree);


	/********************************************/ /**
	 * Resets the camera to the values set when constructing the object
	 ***********************************************/
	void resetCamera();
};