#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../vertex/Vertex.h"
#include "Material.h"

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2

class Mesh
{

public:
	Mesh();
	GLuint VaoID;
	Material *material;
	Matrix4 WorldTransform;

	const void CreateMesh(std::string filename, Material* mat, GLuint UBO_BP);
	std::vector <Vertex> getVertices();
	std::vector <Normal> getNormals();
	std::vector <Texcoord> getTexCoords();
	bool getNormalsLoaded();
	bool getTexcoordsLoaded();
	void setSharedMatrices(const std::string& name, GLuint UBO_BP);
	void Draw();
	void setWorldTransform(Matrix4 transform);
	
private:
	std::vector <Vertex> Vertices, vertexData;
	std::vector <Texcoord> Texcoords, texcoordData;
	std::vector <Normal> Normals, normalData;

	std::vector <unsigned int> vertexIdx, texcoordIdx, normalIdx;

	bool TexcoordsLoaded, NormalsLoaded;


	void parseVertex(std::stringstream& sin);

	void parseTexcoord(std::stringstream& sin);

	void parseNormal(std::stringstream& sin);

	void parseFace(std::stringstream& sin);

	void parseLine(std::stringstream& sin);

	void loadMeshData(std::string& filename);

	void processMeshData();

	void freeMeshData();
	void setupBufferObjects();
};