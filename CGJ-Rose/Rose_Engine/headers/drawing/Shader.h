#pragma once
#include <string>
#include <GL/glew.h>
#include <unordered_map>

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	GLuint m_RendererID;
	std::string m_path;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	Shader(const std::string& path);
	~Shader();

	void SetupShader(bool TexcoordsLoaded=false, bool NormalsLoaded=false);
	void SetupShader(const std::string& path, bool TexcoordsLoaded = false, bool NormalsLoaded = false);

	void Bind() const;
	void UnBind() const;

	// Set uniforms
	void SetUniform4fv(const std::string& name, float matrix[]);
	void SetUniform4fvec(const std::string& name, float vec[]);
	void SetUniform1i(const std::string& name, int value);
	void SetUniformBlock(const std::string& name, GLuint UBO_BP);


private:
	ShaderProgramSource ParseShader(const std::string& path);
	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader, bool TexcoordsLoaded, bool NormalsLoaded);
	GLuint CompileShader(GLuint type, const std::string& source);
	int GetUniformLocation(const std::string& name);
	GLuint GetUniformBlockIndex(const std::string& name);

};

