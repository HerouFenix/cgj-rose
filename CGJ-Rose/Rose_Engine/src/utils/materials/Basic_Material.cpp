#include "../../headers/materials/Basic_Material.h"

Basic_Material::Basic_Material()
{
}

Basic_Material::Basic_Material(Shader sh)
{
	shader = sh;
}

void Basic_Material::setUniforms(Matrix4 model)
{

	//COLOUR///////////////////
	shader.SetUniform4fvec("uniformColour", new float[] {colour.getX(), colour.getY(), colour.getZ(), colour.getW()});

	GLCall(glActiveTexture(GL_TEXTURE0 + texture.ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture.ID));

	//MODEL////////////////////
	float model_arr[16];
	model.getRowMajor(model_arr);
	shader.SetUniform4fv("ModelMatrix", model_arr);

}



void Basic_Material::setColour(Vector4 colour_input)
{
	colour = colour_input;
}
