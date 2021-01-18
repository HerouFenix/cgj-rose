#include "../../headers/materials/Marble_Material.h"

Marble_Material::Marble_Material()
{
}

Marble_Material::Marble_Material(Shader sh)
{
	shader = sh;
}

void Marble_Material::setUniforms(Matrix4 model) {

	//MODEL////////////////////
	float model_arr[16];
	model.getRowMajor(model_arr);
	shader.SetUniform4fv("ModelMatrix", model_arr);

	GLCall(glActiveTexture(GL_TEXTURE0 + depthMap));
	GLCall(glBindTexture(GL_TEXTURE_2D, depthMap));
	shader.SetUniform1i("shadowMap", depthMap);
}

void Marble_Material::setColour(Vector4 colour_input)
{
	colour = colour_input;
}