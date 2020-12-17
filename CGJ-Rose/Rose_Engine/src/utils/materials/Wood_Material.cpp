#include "../../headers/materials/Wood_Material.h"

Wood_Material::Wood_Material()
{
}

Wood_Material::Wood_Material(Shader sh)
{
	shader = sh;
	setTexture("resources/images/wood.png");
}

void Wood_Material::setUniforms(Matrix4 model)
{

	//LIGHT////////////////////
	//shader.SetUniform3fvec("Ambient", new float[] {ambient.getX(), ambient.getY(), ambient.getZ()});
	//shader.SetUniform3fvec("Diffuse", new float[] {diffuse.getX(), diffuse.getY(), diffuse.getZ()});
	//shader.SetUniform3fvec("Specular", new float[] {specular.getX(), specular.getY(), specular.getZ()});
	//shader.SetUniform1f("Shininess", shininess);

	//COLOUR///////////////////
	shader.SetUniform4fvec("uniformColour", new float[] {colour.getX(), colour.getY(), colour.getZ(), colour.getW()});

	GLCall(glActiveTexture(GL_TEXTURE0 + texture.ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture.ID));

	shader.SetUniform1i("u_Texture", texture.ID);

	//MODEL////////////////////
	float model_arr[16];
	model.getRowMajor(model_arr);
	shader.SetUniform4fv("ModelMatrix", model_arr);

}



void Wood_Material::setColour(Vector4 colour_input)
{
	colour = colour_input;
}