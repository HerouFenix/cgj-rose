#include "../../headers/materials/Marble_Material.h"

Marble_Material::Marble_Material()
{
}

Marble_Material::Marble_Material(Shader sh)
{
	shader = sh;
}

void Marble_Material::setUniforms(Matrix4 model) {
	//COLOUR///////////////////
	shader.SetUniform4fvec("uniformColour", new float[] {colour.getX(), colour.getY(), colour.getZ(), colour.getW()});

	//LIGHT_COLOUR/////////////
	shader.SetUniform4fvec("uniformLightColour", new float[] {1.0f, 1.0f, 1.0f, 1.0f});

	//LIGHT_POS/////////////
	shader.SetUniform3fvec("uniformLightPos", new float[] {-4.0f, 13.0f, 3.5f});
	//MODEL////////////////////
	float model_arr[16];
	model.getRowMajor(model_arr);
	shader.SetUniform4fv("ModelMatrix", model_arr);
}

void Marble_Material::setColour(Vector4 colour_input)
{
	colour = colour_input;
}