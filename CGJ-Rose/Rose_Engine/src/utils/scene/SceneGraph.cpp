#include "../../headers/scene/SceneGraph.h"
#include <glm\fwd.hpp>
#include <glm\ext\matrix_transform.hpp>

SceneGraph::SceneGraph()
{
	camera = ArcBallCamera();
	light = Light();
}

SceneGraph::~SceneGraph()
{
}

void SceneGraph::SetCamera(ArcBallCamera c)
{
	camera = c;
}

void SceneGraph::SetLight(Light l)
{
	light = l;
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

SceneNode* SceneGraph::AddNode(Mesh* m, SceneNode* parent)
{
	SceneNode* newNode = new SceneNode(m, parent);
	parent->AddChildNode(newNode);

	return newNode;
}

void SceneGraph::DrawSceneGraph(bool ortho)
{
	camera.RenderCamera(ortho);
	light.RenderLight();
	if (root != NULL) {
		root->Draw();
	}
}

void SceneGraph::DrawSceneGraphDepth(Shader* depthShader)
{
	light.RenderLight();

	depthShader->Bind();

	if (root != NULL) {
		root->DrawDepth(depthShader);
	}

	depthShader->UnBind();
}