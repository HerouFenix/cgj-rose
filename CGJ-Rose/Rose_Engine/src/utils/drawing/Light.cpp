#include "..\..\..\headers\drawing\Light.h"

Light::~Light()
{
}

Light::Light(Vector3 pos, Vector4 col)
{
	position = pos;
	colour = col;

	setViewMatrix();
}

void Light::setProjectionMatrix(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near, GLfloat far)
{
	projMatrix = Matrix4(new float[4][4]{
		{2 / (right - left), 0                 , 0               , (left + right) / (left - right)},
		{0                 , 2 / (top - bottom), 0               , (bottom + top) / (bottom - top)},
		{0                 , 0                 , 2 / (near - far), (near + far) / (near - far)},
		{0                 , 0                 , 0               , 1},
		}
	);
}

void Light::setProjectionMatrix(Matrix4 newProjMatrix)
{
	projMatrix = newProjMatrix;
}

Matrix4 Light::getOrthProj()
{
	return projMatrix;
}

void Light::setPosition(Vector3 newPos)
{
	position = newPos;
	setViewMatrix();
}

Vector3 Light::getPosition()
{
	return position;
}

void Light::setColour(Vector4 newColour)
{
	colour = newColour;
}

Vector4 Light::getColour()
{
	return colour;
}

void Light::SetupLight(GLuint UBO_BP_)
{
	{
		UBO_BP = UBO_BP_;
		glGenBuffers(1, &vbo_id);

		glBindBuffer(GL_UNIFORM_BUFFER, vbo_id);
		{
			glBufferData(GL_UNIFORM_BUFFER, sizeof(float[4]) + sizeof(float[3]) + sizeof(float[16]) * 2, 0, GL_STREAM_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, vbo_id);
		}

		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}

void Light::RenderLight() {
	float proj[16];
	float view[16];
	float pos[3];
	float col[4];

	projMatrix.getColMajor(proj);

	viewMatrix.getColMajor(view);

	pos[0] = position.getX();
	pos[1] = position.getY();
	pos[2] = position.getZ();

	col[0] = colour.getX();
	col[1] = colour.getY();
	col[2] = colour.getZ();
	col[3] = colour.getW();
	int oof = sizeof(col);
	int oof2 = sizeof(float[4]);
	glBindBuffer(GL_UNIFORM_BUFFER, vbo_id);
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float[4]), col);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float[4]), sizeof(float[3]), pos);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float[3]) + sizeof(float[4]), sizeof(float[16]), view);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float[3]) + sizeof(float[4]) + sizeof(float[16]), sizeof(float[16]), proj);
	}

	/*
	float data[4];
	glGetBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float[4]), data);


	float data2[3];
	glGetBufferSubData(GL_UNIFORM_BUFFER, sizeof(float[4]), sizeof(float[3]), data2);


	float data3[16];
	glGetBufferSubData(GL_UNIFORM_BUFFER, sizeof(float[4]) + sizeof(float[3]), sizeof(float[16]), data3);


	float data4[16];
	glGetBufferSubData(GL_UNIFORM_BUFFER, sizeof(float[4]) + sizeof(float[3]) + sizeof(float[16]), sizeof(float[16]), data4);
	*/
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


Matrix4 Light::getViewMatrix()
{
	return viewMatrix;
}

void Light::setViewMatrix()
{
	Vector3 v = (Vector3() - position); // CameraDirection
	if (v != Vector3())
		v = v.normalize();

	Vector3 s = v.crossProd(Vector3(0.0, 1.0, 0.0)); // CameraRight
	if (s != Vector3())
		s = s.normalize();

	Vector3 u = s.crossProd(v); // CameraUp

	Matrix4 axis(new float[4][4]{
			{  s.getX(),  s.getY(),	 s.getZ(), 0},
			{  u.getX(),  u.getY(),	 u.getZ(), 0},
			{ -v.getX(), -v.getY(), -v.getZ(), 0},
			{ 0,         0,		    0,        1}
		});

	Matrix4 trans(new float[4][4]{
			{ 1, 0, 0, -position.getX()},
			{ 0, 1, 0, -position.getY()},
			{ 0, 0, 1, -position.getZ()},
			{ 0, 0, 0,	1		  }
		});

	viewMatrix = axis * trans;
}