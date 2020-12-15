#include "../../headers/drawing/Texture.h"


Texture::Texture()
{
}

Texture::Texture(const std::string& file_path)
	:ID(0), path(file_path), localBuffer(nullptr), 
	width(0), height(0), bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	GLCall(glGenTextures(1, &ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, ID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));

	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (localBuffer) {
		stbi_image_free(localBuffer);
	}
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &ID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, ID));

}

void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
