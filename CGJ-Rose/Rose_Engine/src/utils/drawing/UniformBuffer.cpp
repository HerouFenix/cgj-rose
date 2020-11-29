#include "../../headers/drawing/UniformBuffer.h"
#include "../../headers/drawing/Renderer.h"
#include <iostream>


UniformBuffer::UniformBuffer()
{
	m_VboID = -1;
	UBO_BP = -1;
}

void UniformBuffer::SetupBuffer(const void* data, GLuint size, GLuint UBO_BP_)
{
	UBO_BP = UBO_BP_;
	GLCall(glGenBuffers(1, &m_VboID));

	glBindBuffer(GL_UNIFORM_BUFFER, m_VboID);
	{
		glBufferData(GL_UNIFORM_BUFFER, sizeof(float[16]) * 2, 0, GL_STREAM_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, m_VboID);
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

UniformBuffer::~UniformBuffer()
{
	GLCall(glDeleteBuffers(1, &m_VboID));
}

void UniformBuffer::Bind() const
{
	//std::cout << "Binding to: " << m_VboID << "\n";
	//std::cout << "Mode : " << mode << "  (" << GL_UNIFORM_BUFFER << ")" << "\n\n";

	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_VboID));
}

void UniformBuffer::Unbind() const
{
	//std::cout << "Unbinding to: " << m_VboID << "\n";
	//std::cout << "Mode : " << mode << "  (" << GL_UNIFORM_BUFFER << ")" << "\n\n";

	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));

}

void UniformBuffer::SubBufferData(GLintptr offset, GLuint size, const void* data)
{
	Bind();
	GLCall(glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data));
	Unbind();
}

GLuint UniformBuffer::getID() const
{
	return m_VboID;
}
