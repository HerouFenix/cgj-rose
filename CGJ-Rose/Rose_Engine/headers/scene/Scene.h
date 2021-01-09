#pragma once

// SCENE CLASS HEADER
/// Class used to create new SceneGraphs and manage them
#include<iostream>
#include <vector> 

#include "SceneGraph.h"

#include <cstdlib>  
#include <ctime> 

class Scene {
private:
	std::vector<SceneGraph*> sceneGraphs;
public:
	Scene();
	SceneGraph* CreateSceneGraph();

	std::vector<SceneGraph*> GetSceneGraphs();

	void SetupSceneGraph(SceneGraph* sceneGraph, Mesh meshes[]);

	void ClearScene();
	void DrawSceneGraphs(bool ortho);
	void DrawSceneGraphsDepth(Shader* depthShader);
};
