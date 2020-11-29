#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../vertex/Vertex.h"


class Mesh
{

public:
	Mesh();

	const void CreateMesh(std::string filename);
	std::vector <Vertex> getVertices();
	std::vector <Normal> getNormals();
	std::vector <Texcoord> getTexCoords();
	bool getNormalsLoaded();
	bool getTexcoordsLoaded();
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
};