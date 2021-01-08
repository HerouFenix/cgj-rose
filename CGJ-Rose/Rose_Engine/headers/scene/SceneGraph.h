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
	SceneNode* AddNode(Mesh* m, SceneNode* parent);

	void DrawSceneGraph(bool ortho = false);
	void DrawSceneGraphDepth(Shader* depthShader, Vector3 lightPosition);
};
