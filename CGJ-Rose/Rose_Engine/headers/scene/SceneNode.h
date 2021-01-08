#pragma once
#include  <vector>
#include "../vectors/Vector4.h"
#include "../vectors/Vector3.h"
#include "../matrices/Matrix4.h"
#include "../drawing/Mesh.h"
#include "../drawing/Shader.h"
#include "../drawing/Renderer.h"
#include "../quaternions/Quaternion.h"

// SCENE NODE CLASS
/// Class used to represent a Node on our Scene Graph
/// 
/// Each SceneNode has a local transform, world transform, a colour, and a pointer to a Mesh and shader.

// Based on https://research.ncl.ac.uk/game/mastersdegree/graphicsforgames/scenegraphs/Tutorial%206%20-%20Scene%20Graphs.pdf

class SceneNode {
public:
	Vector3 position;
	Vector3 scale;
	Quaternion rotation;

	bool backCull = true; bool frontCull = false; bool cullDisabled = false;

	SceneNode(Mesh* m, SceneNode* parent = NULL);
	SceneNode();
	~SceneNode();

	void SetPosition(Vector3 pos);
	void SetRotation(Quaternion rt);
	void SetScale(Vector3 sc);

	void SetBackCull(bool cull);
	void SetFrontCull(bool cull);

	void ResetToDefault();

	Matrix4 GetLocalTransform();

	Matrix4 GetWorldTransform();

	Mesh* GetMesh();
	void SetMesh(Mesh* m);

	void AddChildNode(SceneNode* s);

	std::vector<SceneNode*> GetChildNodes();

	void PreDraw();
	virtual void Draw();
	virtual void DrawDepth(Shader* depthShader);
	void PostDraw();

protected:
	SceneNode* parent;
	Mesh* mesh;
	std::vector<SceneNode*> children;
};