#include "../../headers/drawing/VertexBuffer.h"
#include "../../headers/drawing/Renderer.h"


VertexBuffer::VertexBuffer(const void* data, GLuint size)
{
	GLCall(glGenBuffers(1, &m_VboID));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VboID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_VboID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VboID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}

void VertexBuffer::SubBufferData(GLintptr offset, GLuint size, const void* data)
{
	Bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
	Unbind();
}

GLuint VertexBuffer::getID() const
{
	return m_VboID;
}
