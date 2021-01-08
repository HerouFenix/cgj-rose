#pragma once
#include <string>
#include <GL/glew.h>
#include "Shader.h"

class Skybox
{
public:
	void SetShader(Shader shader);
	void SetupSkybox(float far);
	void SetTextures(std::string newFaces[6]);

	void Draw();

private:
	std::string faces[6];
	unsigned int textureID;
	GLuint skyboxVBO;
	GLuint skyboxVAO;
	GLuint UBO_BP = 0;
	Shader skyboxShader;
};