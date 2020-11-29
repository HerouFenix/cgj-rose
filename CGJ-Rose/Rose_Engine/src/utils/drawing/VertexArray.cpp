#include "../../headers/drawing/VertexArray.h"

#include "../../headers/drawing/VertexBufferLayout.h"
#include "../../headers/drawing/Renderer.h"

VertexArray::VertexArray()
{
	m_VaoID = -1;
}

GLuint VertexArray::CreateVertexArray() {
	GLCall(glGenVertexArrays(1, &m_VaoID));
	return m_VaoID;
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_VaoID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	GLuint offset = 0;
	for (GLuint i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	vb.Unbind();
	UnBind();
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_VaoID));
}

void VertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}

GLuint VertexArray::getID() const
{
	return m_VaoID;
}

