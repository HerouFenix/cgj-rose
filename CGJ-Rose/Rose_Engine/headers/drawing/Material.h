#pragma once
#include "Shader.h"
#include "../matrices/Matrix4.h"
#include "../vectors/Vector3.h"
#include "../vectors/Vector4.h"
#include "Texture.h"


class Material
{
public:

	GLuint UBO_ID;
	Shader shader;	

	Vector3 ambient = Vector3();
	Vector3 diffuse = Vector3();
	Vector3 specular = Vector3();
	float shininess = 32.0f;

	Texture texture;

	Vector4 colour = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	float textCoords[6] = 
	{ 0.0f, 0.0f,  // lower-left corner  
	1.0f, 0.0f,  // lower-right corner
	0.5f, 1.0f   // top-center corner
	};


	Material();
	Material(Shader sh);
	void virtual setUniforms(Matrix4 model);
	void setColour(Vector4 colour_input);

	void setTextCoords(float coords[4]);

private:




};

