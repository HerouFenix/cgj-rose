#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
	GLuint m_VaoID;

public:
	VertexArray();
	~VertexArray();
	GLuint CreateVertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;

	GLuint getID() const;
};

