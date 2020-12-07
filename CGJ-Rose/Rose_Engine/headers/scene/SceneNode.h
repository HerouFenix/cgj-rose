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
	Vector3 pos;
	Quaternion quat;
	SceneNode(Mesh* m, SceneNode* parent = NULL, Vector3 sc = Vector3(1,1,1));
	SceneNode();
	~SceneNode();

	void ApplyLocalTransform(Matrix4 transform);

	void SetLocalTransform(Matrix4 transform);


	void ResetToDefaultPosition();

	Matrix4 GetLocalTransform();

	Matrix4 GetWorldTransform();

	Mesh* GetMesh();
	void SetMesh(Mesh* m);



	Vector3 GetScale();
	void SetScale(Vector3 sc);

	void AddChildNode(SceneNode* s);

	std::vector<SceneNode*> GetChildNodes();

	void Update();

	virtual void Draw();

protected:
	SceneNode* parent;
	Mesh* mesh;
	Matrix4 worldTransform;
	Matrix4 localTransform;
	Vector3 scale;
	float colour[4];
	std::vector<SceneNode*> children;
};