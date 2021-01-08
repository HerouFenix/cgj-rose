#include "../../headers/scene/SceneGraph.h"
#include <glm\fwd.hpp>
#include <glm\ext\matrix_transform.hpp>

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

SceneNode* SceneGraph::AddNode(Mesh* m, SceneNode* parent)
{
	SceneNode* newNode = new SceneNode(m, parent);
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

void SceneGraph::DrawSceneGraphDepth(Shader* depthShader, Vector3 lightPosition)
{
	depthShader->Bind();

	//TODO: PROBS CAN BE DONE BETTER?
	Vector3 v = (Vector3() - lightPosition).normalize(); // CameraDirection

	Vector3 s = v.crossProd(Vector3(0.0,1.0,0.0)).normalize(); // CameraRight

	Vector3 u = s.crossProd(v); // CameraUp

	Matrix4 axis(new float[4][4]{
			{  s.getX(),  s.getY(),	 s.getZ(), 0},
			{  u.getX(),  u.getY(),	 u.getZ(), 0},
			{ -v.getX(), -v.getY(), -v.getZ(), 0},
			{ 0,         0,		    0,        1}
		});

	Matrix4 trans(new float[4][4]{
			{ 1, 0, 0, -lightPosition.getX()},
			{ 0, 1, 0, -lightPosition.getY()},
			{ 0, 0, 1, -lightPosition.getZ()},
			{ 0, 0, 0,	1		  }
		});

	Matrix4 lightViewMatrix = axis * trans;
	float view_arr[16];
	lightViewMatrix.getRowMajor(view_arr);

	Matrix4 lightProjectionMatrix = camera.getOrthProj();
	float proj_arr[16];
	lightProjectionMatrix.getRowMajor(proj_arr);

	depthShader->SetUniform4fv("viewMatrix", view_arr);
	depthShader->SetUniform4fv("projMatrix", proj_arr);

	if (root != NULL) {
		root->DrawDepth(depthShader);
	}

	depthShader->UnBind();
}