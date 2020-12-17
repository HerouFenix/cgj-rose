#pragma once
#include "Material.h"
#include <chrono>

class Rose_Material : public Material
{
public:

	Vector4 colour = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	std::chrono::milliseconds  initial_time;

	Rose_Material();
	Rose_Material(Shader sh);
	void setUniforms(Matrix4 model) override;
	void setColour(Vector4 colour_input);

private:

};

