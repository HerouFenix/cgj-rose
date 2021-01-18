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
	shader.SetUniform4fvec("uniformColour", new float[] {colour.getX(), colour.getY(), colour.getZ(), colour.getW()});


	GLCall(glActiveTexture(GL_TEXTURE0 + texture.ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture.ID));

	//MODEL////////////////////
	float model_arr[16];
	model.getRowMajor(model_arr);
	shader.SetUniform4fv("ModelMatrix", model_arr);

	GLCall(glActiveTexture(GL_TEXTURE0 + depthMap));
	GLCall(glBindTexture(GL_TEXTURE_2D, depthMap));
	shader.SetUniform1i("shadowMap", depthMap);
}


void Glass_Material::setColour(Vector4 colour_input)
{
	colour = colour_input;
}
