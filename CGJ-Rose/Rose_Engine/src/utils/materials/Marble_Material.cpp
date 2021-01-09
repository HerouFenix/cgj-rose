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

	//MODEL////////////////////
	float model_arr[16];
	model.getRowMajor(model_arr);
	shader.SetUniform4fv("ModelMatrix", model_arr);
}

void Marble_Material::setColour(Vector4 colour_input)
{
	colour = colour_input;
}