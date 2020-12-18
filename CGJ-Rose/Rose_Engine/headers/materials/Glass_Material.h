#pragma once
#include "Material.h"

class Glass_Material : public Material
{
public:

	Vector4 colour = Vector4(0.776f, 0.886f, 0.890f, 0.15f);

	Glass_Material(bool justBlending = false);
	void setUniforms(Matrix4 model) override;
	void setColour(Vector4 colour_input);

private:

};

