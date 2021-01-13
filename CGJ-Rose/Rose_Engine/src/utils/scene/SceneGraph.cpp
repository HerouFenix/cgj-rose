#include "../../headers/scene/SceneGraph.h"
#include <glm\fwd.hpp>
#include <glm\ext\matrix_transform.hpp>
#include <glm\ext\matrix_clip_space.hpp>

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

void SceneGraph::DrawSceneGraph(bool ortho, bool drawLight)
{
	camera.RenderCamera(ortho);
	light.RenderLight();

	if (drawLight)
		light.DrawLight();


	if (root != NULL) {
		root->Draw();
	}
}

void SceneGraph::DrawSceneGraphDepth(Shader* depthShader)
{
	light.RenderLight();

	depthShader->Bind();

	//float space[16];
	//Matrix4 lightSpace = light.getViewMatrix() * light.getOrthProj();
	//
	//lightSpace.getColMajor(space);
	//depthShader->SetUniform4fv("lightSpaceMatrix",space);


	if (root != NULL) {
		root->DrawDepth(depthShader);
	}

	depthShader->UnBind();
}


