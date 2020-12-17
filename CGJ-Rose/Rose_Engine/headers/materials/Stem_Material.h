#pragma once
#include "Material.h"

class Stem_Material : public Material
{
public:

	Vector4 colour = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

	Stem_Material();
	Stem_Material(Shader sh);
	void setUniforms(Matrix4 model) override;
	void setColour(Vector4 colour_input);

private:

};

