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

	Vector4 colour = Vector4(1.0f, 1.0f, 1.0f, 1.0f);


	Material();
	Material(Shader sh);
	void virtual setUniforms(Matrix4 model);
	void setColour(Vector4 colour_input);

private:




};

