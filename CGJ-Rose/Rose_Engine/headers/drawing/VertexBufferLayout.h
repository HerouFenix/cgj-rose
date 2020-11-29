#pragma once

#include <vector>
#include "Renderer.h"
#include "../vectors/Vector4.h"
struct VertexBufferElement
{
	GLuint type;
	GLuint count;
	unsigned char normalized;

	static GLuint GetSizeOfType(GLuint type)
	{
		switch (type) {
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	GLuint m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) {};

	template<typename T>
	void Push(GLuint count)
	{
		static_assert(false);
	}

	template<>
	void Push <float>(GLuint count)
	{
		m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}
	template<>
	void Push <GLuint>(GLuint count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}
	template<>
	void Push <unsigned char>(GLuint count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}
	template<>
	void Push <Vector4>(GLuint count)
	{
		m_Elements.push_back({ GL_FLOAT, count*4, GL_FALSE });
		m_Stride += sizeof(Vector4);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline GLuint GetStride() const { return m_Stride; }
};

