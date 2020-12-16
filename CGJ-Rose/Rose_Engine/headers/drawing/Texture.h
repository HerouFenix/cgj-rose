
#pragma once
#include <string>
#include "Renderer.h"
#include "stb_image.h"

class Texture
{

public:

	GLuint m_RendererID;
	std::string m_path;
	unsigned char* localBuffer;
	int width, height, bpp;

	Texture();
	Texture(const std::string& path);
	~Texture();

	void setup();

	void Bind(unsigned int slot = 0) const;
};