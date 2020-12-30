#include "../../headers/materials/Material.h"

Material::Material() {

}


Material::Material(Shader sh)
{
	shader = sh;
	texture = _Texture();
}

void Material::setUniforms(Matrix4 model)
{

	//LIGHT////////////////////
	//shader.SetUniform3fvec("Ambient", new float[] {ambient.getX(), ambient.getY(), ambient.getZ()});
	//shader.SetUniform3fvec("Diffuse", new float[] {diffuse.getX(), diffuse.getY(), diffuse.getZ()});
	//shader.SetUniform3fvec("Specular", new float[] {specular.getX(), specular.getY(), specular.getZ()});
	//shader.SetUniform1f("Shininess", shininess);

	//COLOUR///////////////////
	//shader.SetUniform4fvec("uniformColour", new float[] {colour.getX(), colour.getY(), colour.getZ(), colour.getW()});

	//MODEL////////////////////
	float model_arr[16];
	model.getRowMajor(model_arr);
	shader.SetUniform4fv("ModelMatrix", model_arr);

}


void Material::setTextCoords(float coords[4]) {
	for (int i = 0; i < 4; i++) {
		textCoords[i] = coords[i];
	}
}

void Material::setTexture(const std::string& path) {
	glGenTextures(1, &texture.ID);
	glBindTexture(GL_TEXTURE_2D, texture.ID);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load and generate the texture
	unsigned char* data = stbi_load(path.c_str(), &texture.width, &texture.height, &texture.bpp, 3);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}
