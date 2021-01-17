#pragma once
#include <string>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <unordered_map>

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
	std::string GeometrySource;
};

class Shader
{
public:
	GLuint m_RendererID;
	std::string m_path;
	std::unordered_map<std::string, int> m_UniformLocationCache;

	Shader();
	Shader(const std::string& path);
	~Shader();

	void SetupShader(bool TexcoordsLoaded = false, bool NormalsLoaded = false, bool geometry = false);
	void SetupShader_VsFsGs(bool TexcoordsLoaded, bool NormalsLoaded);
	void SetupShader(const std::string& path, bool TexcoordsLoaded = false, bool NormalsLoaded = false);

	void Bind() const;
	void UnBind() const;

	void SetUniform3fv_glm(const std::string& name, const glm::vec3 vVector);

	void SetUniform3fv_glm(const std::string& name, glm::vec3* vVector);

	void SetUniformMatrix4fv_glm(const std::string& name, const glm::mat4 mMatrix);

	void SetUniformMatrix4fv_glm(const std::string& name, glm::mat4* mMatrix);

	// Set uniforms
	void SetUniform4fv(const std::string& name, float matrix[]);
	void SetUniform4fvec(const std::string& name, float vec[]);
	void SetUniform3fvec(const std::string& name, float vec[]);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniformBlock(const std::string& name, GLuint UBO_BP);


private:
	ShaderProgramSource ParseShader(const std::string& path);
	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader, bool TexcoordsLoaded, bool NormalsLoaded, bool geometry = false);
	GLuint CreateShader_VsFsGs(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader, bool TexcoordsLoaded, bool NormalsLoaded);
	GLuint CompileShader(GLuint type, const std::string& source);
	int GetUniformLocation(const std::string& name);
	GLuint GetUniformBlockIndex(const std::string& name);

};

