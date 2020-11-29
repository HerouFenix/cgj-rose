#pragma once

// SCENE CLASS HEADER
/// Class used to create new SceneGraphs and manage them
#include<iostream>
#include <vector> 

#include "SceneGraph.h"
#include "../shapes/Tetromino.h"

#include <cstdlib>  
#include <ctime> 

class Scene {
private:
	std::vector<SceneGraph*> sceneGraphs;
public:
	Scene();
	SceneGraph* CreateSceneGraph();
	SceneGraph* CreateSceneGraph(ArcBallCamera c);

	std::vector<SceneGraph*> GetSceneGraphs();

	void SetupTetrominoSceneGraph(SceneGraph* sceneGraph, Mesh* m, Shader* s);

	void ClearScene();
	void DrawSceneGraphs(bool ortho);
};
