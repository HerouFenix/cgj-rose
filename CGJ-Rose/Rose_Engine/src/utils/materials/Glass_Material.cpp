#include "../../headers/materials/Glass_Material.h"

Glass_Material::Glass_Material(bool justBlending)
{
	if (justBlending) {
		shader = Shader("resources/shaders/Basic3D.shader");
	}
	else {
		shader = Shader("resources/shaders/Glass.shader");
	}

	transparent = true;
}

void Glass_Material::setUniforms(Matrix4 model)
{


	//COLOUR///////////////////
	float values[4] = { colour.getX(), colour.getY(), colour.getZ(), colour.getW() };
	shader.SetUniform4fvec("uniformColour", values);


	GLCall(glActiveTexture(GL_TEXTURE0 + texture.ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture.ID));

	//MODEL////////////////////
	float model_arr[16];
	model.getRowMajor(model_arr);
	shader.SetUniform4fv("ModelMatrix", model_arr);

}


void Glass_Material::setColour(Vector4 colour_input)
{
	colour = colour_input;
}
