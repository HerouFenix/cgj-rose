#include "../../headers/drawing/Texture.h"
#include <iostream>

Texture::Texture()
{
}

Texture::Texture(const std::string& path)
	:m_path(path), m_RendererID(0), localBuffer(nullptr), width(0), height(0), bpp(0)
{
	setup();
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::setup()
	
{
	std::cout << "Before Creation: " << m_RendererID << std::endl;

	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(m_path.c_str(), &width, &height, &bpp, 4);

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));

	if (localBuffer) {
		stbi_image_free(localBuffer);
	}

	std::cout << "After Creation: " << m_RendererID << std::endl;

}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	std::cout << "Bind: " << m_RendererID << std::endl;
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

}
