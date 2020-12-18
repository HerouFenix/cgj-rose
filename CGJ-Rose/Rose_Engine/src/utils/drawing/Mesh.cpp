#include "../../headers/drawing/Mesh.h"


Mesh::Mesh()
{
	NormalsLoaded = false;
	TexcoordsLoaded = false;
	VaoID = -1;
}

const void Mesh::CreateMesh(std::string filename, Material* mat, GLuint UBO_BP)
{
	NormalsLoaded = false;
	TexcoordsLoaded = false;

	material = mat;

	loadMeshData(filename);
	processMeshData();
	setupBufferObjects();

	material->shader.SetupShader();

	material->shader.SetUniformBlock("SharedMatrices", UBO_BP);

	freeMeshData();
}

const void Mesh::CreateMesh(std::string filename, Material* mat)
{
	NormalsLoaded = false;
	TexcoordsLoaded = false;

	material = mat;

	loadMeshData(filename);
	processMeshData();
	freeMeshData();
}

std::vector<Vertex> Mesh::getVertices()
{
	return Vertices;
}

std::vector<Normal> Mesh::getNormals()
{
	return Normals;
}

std::vector<Texcoord> Mesh::getTexCoords()
{
	return Texcoords;
}

bool Mesh::getNormalsLoaded() {
	return NormalsLoaded;
}

bool Mesh::getTexcoordsLoaded() {
	return TexcoordsLoaded;
}

void Mesh::setSharedMatrices(const std::string& name, GLuint UBO_BP)
{
	material->shader.Bind();
	material->shader.SetUniformBlock(name, UBO_BP);
	material->shader.UnBind();
}

void Mesh::Draw(bool cullFaces, bool backCull)
{
	if (cullFaces) {
		//glDepthMask(GL_FALSE);
		glEnable(GL_CULL_FACE);

		if (backCull) {
			glCullFace(GL_BACK);
		}
		else {
			glCullFace(GL_FRONT);
		}
	}

	glBindVertexArray(VaoID);
	material->shader.Bind();

	material->setUniforms(WorldTransform);

	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)Vertices.size());

	glBindVertexArray(0);
	material->shader.UnBind();

	if (cullFaces) {
		//glDepthMask(GL_TRUE);
		glDisable(GL_CULL_FACE);
	}
}

void Mesh::setWorldTransform(Matrix4 transform)
{
	WorldTransform = transform;
}

void Mesh::setMaterial(Material* mat, GLuint UBO_BP)
{
	material = mat;
}

void Mesh::parseVertex(std::stringstream& sin)
{
	Vertex v;
	sin >> v.x >> v.y >> v.z;
	vertexData.push_back(v);
}

void Mesh::parseTexcoord(std::stringstream& sin)
{
	Texcoord t;
	sin >> t.u >> t.v;
	texcoordData.push_back(t);
}

void Mesh::parseNormal(std::stringstream& sin)
{
	Normal n;
	sin >> n.nx >> n.ny >> n.nz;
	normalData.push_back(n);
}

void Mesh::parseFace(std::stringstream& sin)
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

void Mesh::parseLine(std::stringstream& sin)
{
	std::string s;
	sin >> s;
	if (s.compare("v") == 0) parseVertex(sin);
	else if (s.compare("vt") == 0) parseTexcoord(sin);
	else if (s.compare("vn") == 0) parseNormal(sin);
	else if (s.compare("f") == 0) parseFace(sin);
}

void Mesh::loadMeshData(std::string& filename)
{
	std::ifstream ifile(filename);
	std::string line;
	while (std::getline(ifile, line))
	{
		std::stringstream sline(line);
		parseLine(sline);
	}
	TexcoordsLoaded = (texcoordIdx.size() > 0);
	NormalsLoaded = (normalIdx.size() > 0);
}

void Mesh::processMeshData()
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

void Mesh::freeMeshData()
{
	vertexData.clear();
	texcoordData.clear();
	normalData.clear();
	vertexIdx.clear();
	texcoordIdx.clear();
	normalIdx.clear();
}

void Mesh::setupShader(GLuint UBO_BP)
{
	material->shader.SetupShader(getTexcoordsLoaded(), getNormalsLoaded());
	material->shader.SetUniformBlock("SharedMatrices", UBO_BP);
}

void Mesh::setupBufferObjects() {
	GLuint VboVertices, VboTexcoords, VboNormals;

	glGenVertexArrays(1, &VaoID);
	glBindVertexArray(VaoID);
	{
		glGenBuffers(1, &VboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, VboVertices);
		glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(VERTICES);
		glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		if (getTexcoordsLoaded())
		{
			glGenBuffers(1, &VboTexcoords);
			glBindBuffer(GL_ARRAY_BUFFER, VboTexcoords);
			glBufferData(GL_ARRAY_BUFFER, Texcoords.size() * sizeof(Texcoord), &Texcoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEXCOORDS);
			glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Texcoord), 0);
		}
		if (getNormalsLoaded())
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