#include "../../headers/scene/SceneGraph.h"

SceneGraph::SceneGraph(ArcBallCamera c)
{
	camera = c;
}

SceneGraph::~SceneGraph()
{
}

void SceneGraph::SetCamera(ArcBallCamera c)
{
	camera = c;
}

SceneNode* SceneGraph::GetRoot()
{
	return root;
}

SceneNode* SceneGraph::AddNode()
{
	SceneNode* newNode = new SceneNode();
	if (root == NULL) {
		root = newNode;
	}
	else {
		root->AddChildNode(newNode);
	}

	return newNode;
}

SceneNode* SceneGraph::AddNode(Mesh* m, SceneNode* parent, Vector3 sc)
{
	SceneNode* newNode = new SceneNode(m, parent, sc);
	parent->AddChildNode(newNode);

	return newNode;
}

void SceneGraph::DrawSceneGraph(bool ortho)
{
	camera.RenderCamera(ortho);
	if (root != NULL) {
		root->Draw();
	}
}
