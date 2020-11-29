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

SceneNode* SceneGraph::AddNode(Mesh* m, Shader* s, float* c, Vector3 sc)
{
	SceneNode* newNode = new SceneNode(m, s, c, sc);
	if (root == NULL) {
		root = newNode;
	}
	else {
		root->AddChildNode(newNode);
	}

	return newNode;
}

SceneNode* SceneGraph::AddNode(Mesh* m, Shader* s, SceneNode* parent, float* c, Vector3 sc)
{
	SceneNode* newNode = new SceneNode(m, s, c, sc);
	parent->AddChildNode(newNode);

	return newNode;
}

SceneNode* SceneGraph::AddNode(Mesh* m, Shader* s, Tetromino t, Vector3 sc)
{
	SceneNode* newNode = new SceneNodeTetromino(m, s, t, sc);
	if (root == NULL) {
		root = newNode;
	}
	else {
		root->AddChildNode(newNode);
	}

	return newNode;
}

SceneNode* SceneGraph::AddNode(Mesh* m, Shader* s, SceneNode* parent, Tetromino t, Vector3 sc)
{
	SceneNode* newNode = new SceneNodeTetromino(m, s, t, sc);
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
