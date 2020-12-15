
#pragma once
#include <string>
#include "Renderer.h"

#include "stb_image.h"

class Texture
{
private:
	unsigned int ID;
	std::string path;
	unsigned char* localBuffer;
	int width, height, bpp;

public:

	Texture();

	Texture(const std::string& file_path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind();
};

