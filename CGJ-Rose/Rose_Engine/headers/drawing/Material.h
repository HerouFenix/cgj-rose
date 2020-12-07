#pragma once
#include "Shader.h"
#include "../matrices/Matrix4.h"
#include "../vectors/Vector3.h"
#include "../vectors/Vector4.h"


class Material
{
public:

	GLuint UBO_ID;
	Shader shader;	

	Vector3 ambient = Vector3();
	Vector3 diffuse = Vector3();
	Vector3 specular = Vector3();
	float shininess = 32.0f;

	Material();
	virtual void setUniforms(Matrix4 model) {};

private:




};

