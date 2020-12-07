#include "../../headers/drawing/Basic_Material.h"

Basic_Material::Basic_Material()
{
}

Basic_Material::Basic_Material(Shader sh)
{
	shader = sh;
}

void Basic_Material::setUniforms(Matrix4 model)
{

	//LIGHT////////////////////
	shader.SetUniform4fv("Ambient", new float[] {ambient.getX(), ambient.getY(), ambient.getZ()});
	shader.SetUniform4fv("Diffuse", new float[] {diffuse.getX(), diffuse.getY(), diffuse.getZ()});
	shader.SetUniform4fv("Specular", new float[] {specular.getX(), specular.getY(), specular.getZ()});
	shader.SetUniform1f("Shininess", shininess);

	//COLOUR///////////////////
	shader.SetUniform4fvec("uniformColour", new float[] {colour.getX(), colour.getY(), colour.getZ(), colour.getW()});

	//MODEL////////////////////
	float model_arr[16];
	model.getRowMajor(model_arr);
	shader.SetUniform4fv("ModelMatrix", model_arr);

}



void Basic_Material::setColour(Vector4 colour_input)
{
	colour = colour_input;
}
