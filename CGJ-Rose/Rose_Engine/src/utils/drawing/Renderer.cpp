#include "../../headers/drawing/Renderer.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << "\n";
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum mode)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(mode, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}

void Renderer::DrawObject(GLsizei size, Shader& shader,float* model)
{
	shader.Bind();

	shader.SetUniform4fv("ModelMatrix", model);

	glDrawArrays(GL_TRIANGLES, 0, size);

	glUseProgram(0);
}

void Renderer::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);

}
