#pragma once
#include <GL\glew.h>
class UniformBuffer
{
private:
	GLuint m_VboID;
	GLuint UBO_BP;
public:
	UniformBuffer();
	void SetupBuffer(const void* data, GLuint size, GLuint UBO_BP);
	~UniformBuffer();

	void Bind() const;
	void Unbind() const;

	void SubBufferData(GLintptr offset, GLuint size, const void* data);

	GLuint getID() const;
};

