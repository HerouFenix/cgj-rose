#pragma once
#include "../matrices/Matrix4.h"
#include "../vectors/Vector3.h"
#include "../../../CGJ-Engine/dependencies/glew/include/GL/glew.h"
#include "../quaternions/Quaternion.h"

// ARC BALL CAMERA CLASS HEADER

/// Class used to represent and control an Arc-Ball camera

class Light
{
private:
	Vector3 position;
	Vector4 colour;
	GLuint vbo_id;
	Matrix4 projMatrix;
	Matrix4 viewMatrix;

public:
	GLuint UBO_BP;
	Light(Vector3 pos = Vector3(0, 0, 0), Vector4 col = Vector4(1.0, 1.0, 1.0, 1.0));
	~Light();

	void setProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far);
	void setProjectionMatrix(Matrix4 newProjMatrix);

	Matrix4 getOrthProj();

	Matrix4 getViewMatrix();

	void setPosition(Vector3 newPos);

	Vector3 getPosition();

	void setColour(Vector4 newColour);

	Vector4 getColour();

	void RenderLight();

	void SetupLight(GLuint UBO_BP_);
private:
	void setViewMatrix();
};