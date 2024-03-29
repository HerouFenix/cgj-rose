#include "../../headers/materials/Particle_Material.h"

Particle_Material::Particle_Material()
{
}

Particle_Material::Particle_Material(Shader sh)
{
	shader = sh;
}

void Particle_Material::setUniforms(Matrix4 model)
{
	//COLOUR///////////////////
	float values[4] = { colour.getX(), colour.getY(), colour.getZ(), colour.getW() };
	shader.SetUniform4fvec("u_Color", values);

	//MODEL////////////////////
	float model_arr[16];
	model.getRowMajor(model_arr);
	shader.SetUniform4fv("ModelMatrix", model_arr);

}



void Particle_Material::setColour(Vector4 colour_input)
{
	colour = colour_input;
}
