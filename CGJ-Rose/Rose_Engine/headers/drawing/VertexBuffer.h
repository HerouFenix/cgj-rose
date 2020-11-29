#pragma once
#include <GL\glew.h>
class VertexBuffer
{
private:
	GLuint m_VboID;
public:
	VertexBuffer(const void* data, GLuint size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void SubBufferData(GLintptr offset, GLuint size, const void* data);

	GLuint getID() const;
};

