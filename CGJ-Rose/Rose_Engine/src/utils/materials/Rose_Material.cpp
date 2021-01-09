#include "../../headers/materials/Rose_Material.h"
#include <time.h>
#include <chrono>

Rose_Material::Rose_Material()
{
	
}

Rose_Material::Rose_Material(Shader sh)
{
	shader = sh;
	initial_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	setTexture("resources/images/rose5.jpg");
}

void Rose_Material::setUniforms(Matrix4 model)
{

	//LIGHT////////////////////
	//shader.SetUniform3fvec("Ambient", new float[] {ambient.getX(), ambient.getY(), ambient.getZ()});
	//shader.SetUniform3fvec("Diffuse", new float[] {diffuse.getX(), diffuse.getY(), diffuse.getZ()});
	//shader.SetUniform3fvec("Specular", new float[] {specular.getX(), specular.getY(), specular.getZ()});
	//shader.SetUniform1f("Shininess", shininess);

	std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) - initial_time;
	shader.SetUniform1f("time_U", elapsed.count()/1000.0f);
	
	GLCall(glActiveTexture(GL_TEXTURE0 + texture.ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture.ID));

	shader.SetUniform1i("u_Texture", texture.ID);

	//MODEL////////////////////
	float model_arr[16];
	model.getRowMajor(model_arr);
	shader.SetUniform4fv("ModelMatrix", model_arr);

}

void Rose_Material::setColour(Vector4 colour_input)
{
	colour = colour_input;
}
