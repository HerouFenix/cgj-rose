/*
#include "../../headers/drawing/Obj_Loader.h"


Obj_Loader::Obj_Loader()
{
}

void Obj_Loader::setup(std::string mesh_dir, std::string vs, std::string fs) {

	createMesh(mesh_dir);
	createBufferObjects();
	createShaderProgram(vs, fs);
}

const std::string Obj_Loader::read(const std::string& filename)
{
	std::ifstream ifile(filename);
	std::string shader_string, line;
	while (std::getline(ifile, line))
	{
		shader_string += line + "\n";
	}
	return shader_string;
}

const GLuint Obj_Loader::checkCompilation(const GLuint shader_id, const std::string& filename)
{
	GLint compiled;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
		GLchar* const log = new char[length];
		glGetShaderInfoLog(shader_id, length, &length, log);
		std::cerr << "[" << filename << "] " << std::endl << log;
		delete[] log;
		exit(EXIT_FAILURE);
	}
	return compiled;
}

void Obj_Loader::checkLinkage(const GLuint program_id) {
	GLint linked;
	glGetProgramiv(program_id, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);
		GLchar* const log = new char[length];
		glGetProgramInfoLog(program_id, length, &length, log);
		std::cerr << "[LINK] " << std::endl << log << std::endl;
		delete[] log;
		exit(EXIT_FAILURE);
	}
}

const GLuint Obj_Loader::addShader(const GLuint program_id, const GLenum shader_type, const std::string& filename)
{
	const GLuint shader_id = glCreateShader(shader_type);
	const std::string scode = read(filename);
	const GLchar* code = scode.c_str();
	glShaderSource(shader_id, 1, &code, 0);
	glCompileShader(shader_id);
	checkCompilation(shader_id, filename);
	glAttachShader(program_id, shader_id);
	return shader_id;
}

void Obj_Loader::createShaderProgram(std::string& vs_file, std::string& fs_file)
{
	ProgramId = glCreateProgram();

	GLuint VertexShaderId = addShader(ProgramId, GL_VERTEX_SHADER, vs_file);
	GLuint FragmentShaderId = addShader(ProgramId, GL_FRAGMENT_SHADER, fs_file);

	glBindAttribLocation(ProgramId, VERTICES, "inPosition");
	if (TexcoordsLoaded)
		glBindAttribLocation(ProgramId, TEXCOORDS, "inTexcoord");
	if (NormalsLoaded)
		glBindAttribLocation(ProgramId, NORMALS, "inNormal");

	glLinkProgram(ProgramId);
	checkLinkage(ProgramId);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);
	glDeleteShader(VertexShaderId);
	glDeleteShader(FragmentShaderId);

	ModelMatrix_UId = glGetUniformLocation(ProgramId, "ModelMatrix");
	ViewMatrix_UId = glGetUniformLocation(ProgramId, "ViewMatrix");
	ProjectionMatrix_UId = glGetUniformLocation(ProgramId, "ProjectionMatrix");
}

void Obj_Loader::destroyShaderProgram()
{
	glUseProgram(0);
	glDeleteProgram(ProgramId);
}

////////////////////////////////////////////////////////////////////////// MESH

typedef struct {
	GLfloat x, y, z;
} Vertex;

typedef struct {
	GLfloat u, v;
} Texcoord;

typedef struct {
	GLfloat nx, ny, nz;
} Normal;

std::vector <Vertex> Vertices, vertexData;
std::vector <Texcoord> Texcoords, texcoordData;
std::vector <Normal> Normals, normalData;

std::vector <unsigned int> vertexIdx, texcoordIdx, normalIdx;

void Obj_Loader::parseVertex(std::stringstream& sin)
{
	Vertex v;
	sin >> v.x >> v.y >> v.z;
	vertexData.push_back(v);
}

void Obj_Loader::parseTexcoord(std::stringstream& sin)
{
	Texcoord t;
	sin >> t.u >> t.v;
	texcoordData.push_back(t);
}

void Obj_Loader::parseNormal(std::stringstream& sin)
{
	Normal n;
	sin >> n.nx >> n.ny >> n.nz;
	normalData.push_back(n);
}

void Obj_Loader::parseFace(std::stringstream& sin)
{
	std::string token;
	if (normalData.empty() && texcoordData.empty())
	{
		for (int i = 0; i < 3; i++)
		{
			sin >> token;
			vertexIdx.push_back(std::stoi(token));
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			std::getline(sin, token, '/');
			if (token.size() > 0) vertexIdx.push_back(std::stoi(token));
			std::getline(sin, token, '/');
			if (token.size() > 0) texcoordIdx.push_back(std::stoi(token));
			std::getline(sin, token, ' ');
			if (token.size() > 0) normalIdx.push_back(std::stoi(token));
		}
	}
}

void Obj_Loader::parseLine(std::stringstream& sin)
{
	std::string s;
	sin >> s;
	if (s.compare("v") == 0) parseVertex(sin);
	else if (s.compare("vt") == 0) parseTexcoord(sin);
	else if (s.compare("vn") == 0) parseNormal(sin);
	else if (s.compare("f") == 0) parseFace(sin);
}

void Obj_Loader::loadMeshData(std::string& filename)
{
	std::ifstream ifile(filename);
	std::string line;
	while (std::getline(ifile, line)) {
		std::stringstream sline(line);
		parseLine(sline);
	}
	TexcoordsLoaded = (texcoordIdx.size() > 0);
	NormalsLoaded = (normalIdx.size() > 0);
}

void Obj_Loader::processMeshData()
{
	for (unsigned int i = 0; i < vertexIdx.size(); i++) {
		unsigned int vi = vertexIdx[i];
		Vertex v = vertexData[vi - 1];
		Vertices.push_back(v);
		if (TexcoordsLoaded)
		{
			unsigned int ti = texcoordIdx[i];
			Texcoord t = texcoordData[ti - 1];
			Texcoords.push_back(t);
		}
		if (NormalsLoaded)
		{
			unsigned int ni = normalIdx[i];
			Normal n = normalData[ni - 1];
			Normals.push_back(n);
		}
	}
}

void Obj_Loader::freeMeshData()
{
	vertexData.clear();
	texcoordData.clear();
	normalData.clear();
	vertexIdx.clear();
	texcoordIdx.clear();
	normalIdx.clear();
}

const void Obj_Loader::createMesh(std::string& filename)
{
	loadMeshData(filename);
	processMeshData();
	freeMeshData();
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

void Obj_Loader::createBufferObjects()
{
	GLuint VboVertices, VboTexcoords, VboNormals;

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);
	{
		glGenBuffers(1, &VboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, VboVertices);
		glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		if (TexcoordsLoaded)
		{
			glGenBuffers(1, &VboTexcoords);
			glBindBuffer(GL_ARRAY_BUFFER, VboTexcoords);
			glBufferData(GL_ARRAY_BUFFER, Texcoords.size() * sizeof(Texcoord), &Texcoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXCOORDS);
			glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Texcoord), 0);
		}
		if (NormalsLoaded)
		{
			glGenBuffers(1, &VboNormals);
			glBindBuffer(GL_ARRAY_BUFFER, VboNormals);
			glBufferData(GL_ARRAY_BUFFER, Normals.size() * sizeof(Normal), &Normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMALS);
			glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(Normal), 0);
		}
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboVertices);
	glDeleteBuffers(1, &VboTexcoords);
	glDeleteBuffers(1, &VboNormals);
}

void Obj_Loader::destroyBufferObjects()
{
	glBindVertexArray(VaoId);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(TEXCOORDS);
	glDisableVertexAttribArray(NORMALS);
	glDeleteVertexArrays(1, &VaoId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Obj_Loader::drawObj(GLfloat* model, GLfloat* view, GLfloat* proj, Vector4 color)
{
	glBindVertexArray(VaoId);
	glUseProgram(ProgramId);

	glUniformMatrix4fv(ModelMatrix_UId, 1, GL_FALSE, model);
	glUniformMatrix4fv(ViewMatrix_UId, 1, GL_FALSE, view);
	glUniformMatrix4fv(ProjectionMatrix_UId, 1, GL_FALSE, proj);

	Color_UId = glGetUniformLocation(ProgramId, "ourColor");
	glUniform4f(Color_UId, color.getX(), color.getY(), color.getZ(), color.getW());
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)Vertices.size());

	glUseProgram(0);
	glBindVertexArray(0);
}
*/