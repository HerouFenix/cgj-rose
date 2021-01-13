#pragma once
#include "../camera/ArcBallCamera.h"
#include "../vectors/Vector3.h"
#include "SceneNode.h"
#include "../drawing/Light.h"

class SceneGraph {
private:
	SceneNode* root;
public:
	ArcBallCamera camera;
	Light light;

	SceneGraph();
	~SceneGraph();

	void SetCamera(ArcBallCamera c);
	void SetLight(Light l);

	SceneNode* GetRoot();

	SceneNode* AddNode();
	SceneNode* AddNode(Mesh* m, SceneNode* parent);

	void DrawSceneGraph(bool ortho = false, bool drawLight = false);
	void DrawSceneGraphDepth(Shader* depthShader);
};
