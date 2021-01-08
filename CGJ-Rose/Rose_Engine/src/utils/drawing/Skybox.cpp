#include "../../../headers/drawing/Skybox.h"
#include "../../../headers/materials/stb_image.h"
#include <iostream>

void Skybox::SetShader(Shader shader)
{
	skyboxShader = shader;
}

void Skybox::SetupSkybox(float far)
{
	float skyboxVertices[] = {
		// positions          
		-far,  far, -far,
		-far, -far, -far,
		 far, -far, -far,
		 far, -far, -far,
		 far,  far, -far,
		-far,  far, -far,

		-far, -far,  far,
		-far, -far, -far,
		-far,  far, -far,
		-far,  far, -far,
		-far,  far,  far,
		-far, -far,  far,

		 far, -far, -far,
		 far, -far,  far,
		 far,  far,  far,
		 far,  far,  far,
		 far,  far, -far,
		 far, -far, -far,

		-far, -far,  far,
		-far,  far,  far,
		 far,  far,  far,
		 far,  far,  far,
		 far, -far,  far,
		-far, -far,  far,

		-far,  far, -far,
		 far,  far, -far,
		 far,  far,  far,
		 far,  far,  far,
		-far,  far,  far,
		-far,  far, -far,

		-far, -far, -far,
		-far, -far,  far,
		 far, -far, -far,
		 far, -far, -far,
		-far, -far,  far,
		 far, -far,  far
	};

	// Setup cube vao

	GLuint skyboxVBO;

	glGenVertexArrays(1, &skyboxVAO);
	glBindVertexArray(skyboxVAO);
	{
		glGenBuffers(1, &skyboxVBO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	skyboxShader.SetupShader(false, false);
	skyboxShader.SetUniformBlock("SharedMatrices", UBO_BP);
}

void Skybox::SetTextures(std::string newFaces[6])
{
	for (int i = 0; i < 6; i++) {
		faces[i] = newFaces[i];
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < 6; i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::Draw()
{
	glDepthMask(GL_FALSE);
	glBindVertexArray(skyboxVAO);
	skyboxShader.Bind();

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
	skyboxShader.UnBind();
	glDepthMask(GL_TRUE);
}
