#pragma once
#include "../camera/ArcBallCamera.h"
#include "../vectors/Vector3.h"
#include "SceneNode.h"

class SceneGraph {
private:
	SceneNode* root;
public:
	ArcBallCamera camera;

	SceneGraph(ArcBallCamera c = NULL);
	~SceneGraph();

	void SetCamera(ArcBallCamera c);

	SceneNode* GetRoot();

	SceneNode* AddNode();
	SceneNode* AddNode(Mesh* m, SceneNode* parent, Vector3 sc = Vector3(1, 1, 1));

	void DrawSceneGraph(bool ortho = false);
};
