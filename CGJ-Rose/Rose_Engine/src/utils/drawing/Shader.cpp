#include "../../headers/drawing/Shader.h"
#include "../../headers/drawing/Renderer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& path)
	:m_path(path), m_RendererID(0)
{
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::SetupShader(bool TexcoordsLoaded, bool NormalsLoaded)
{
	ShaderProgramSource source = ParseShader(m_path);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource, TexcoordsLoaded, NormalsLoaded);
}

void Shader::SetupShader(const std::string& path, bool TexcoordsLoaded, bool NormalsLoaded)
{
	m_path = path;
	ShaderProgramSource source = ParseShader(m_path);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource, TexcoordsLoaded, NormalsLoaded);
}

ShaderProgramSource Shader::ParseShader(const std::string& path)
{

	std::ifstream stream(path);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

GLuint Shader::CompileShader(GLuint type, const std::string& source)
{
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader! \n";
		std::cout << message << "\n";
		glDeleteShader(id);
		return 0;
	}

	return id;
}

GLuint Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader, bool TexcoordsLoaded, bool NormalsLoaded)
{
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glBindAttribLocation(program, VERTICES, "inPosition");
	if (TexcoordsLoaded)
		glBindAttribLocation(program, TEXCOORDS, "inTexcoord");
	if (NormalsLoaded)
		glBindAttribLocation(program, NORMALS, "inNormal");

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4fv(const std::string& name, float matrix[])
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_TRUE, matrix));
}

void Shader::SetUniform4fvec(const std::string& name, float vec[])
{
	GLCall(glUniform4fv(GetUniformLocation(name), 1, vec));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniformBlock(const std::string& name, GLuint UBO_BP)
{
	GLCall(glUniformBlockBinding(m_RendererID, GetUniformBlockIndex(name), UBO_BP));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	m_UniformLocationCache[name] = location;
	return location;
}

GLuint Shader::GetUniformBlockIndex(const std::string& name)
{
	GLCall(GLuint UboId = glGetUniformBlockIndex(m_RendererID, name.c_str()));
	if (UboId == -1)
		std::cout << "Warning: Uniform Block '" << name << "' doesn't exist!" << std::endl;
	return UboId;
}
