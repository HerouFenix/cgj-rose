#include "../../headers/materials/Stem_Material.h"

Stem_Material::Stem_Material()
{
}

Stem_Material::Stem_Material(Shader sh)
{
	shader = sh;
	setTexture("resources/images/stem.png");
}

void Stem_Material::setUniforms(Matrix4 model)
{

	//COLOUR///////////////////
	float values[4] = { colour.getX(), colour.getY(), colour.getZ(), colour.getW() };
	shader.SetUniform4fvec("uniformColour", values);

	GLCall(glActiveTexture(GL_TEXTURE0 + texture.ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture.ID));

	shader.SetUniform1i("u_Texture", texture.ID);

	//MODEL////////////////////
	float model_arr[16];
	model.getRowMajor(model_arr);
	shader.SetUniform4fv("ModelMatrix", model_arr);

	GLCall(glActiveTexture(GL_TEXTURE0 + depthMap));
	GLCall(glBindTexture(GL_TEXTURE_2D, depthMap));
	shader.SetUniform1i("shadowMap", depthMap);

}



void Stem_Material::setColour(Vector4 colour_input)
{
	colour = colour_input;
}
