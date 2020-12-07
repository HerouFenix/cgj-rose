#include "../../headers/scene/SceneNode.h"


SceneNode::SceneNode(Mesh* m, SceneNode* parent_node, Vector3 sc) {
	mesh = m;
	parent = parent_node;
	scale = sc;

	localTransform = Matrix4::identity();
	worldTransform = localTransform;
}

SceneNode::SceneNode() {
	scale = Vector3(1,1,1);
	localTransform = Matrix4::identity();
	worldTransform = localTransform;
}


SceneNode::~SceneNode()
{
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete  children[i];
	}
}

void SceneNode::ApplyLocalTransform(Matrix4 transform)
{
	localTransform = transform * localTransform;
	quat = Quaternion(transform.getRotation());
	Vector4 pos4_i(pos.getX(), pos.getY(), pos.getZ(), 1.0f);
	Vector4 pos4_f = pos4_i.transform(transform);
	pos = Vector3(pos4_f.getX(), pos4_f.getY(), pos4_f.getZ());

	Update();
}

void SceneNode::SetLocalTransform(Matrix4 transform)
{
	localTransform = transform;
	Update();
}

void SceneNode::ResetToDefaultPosition() {
	localTransform = Matrix4::identity();
}

Matrix4 SceneNode::GetLocalTransform()
{
	return localTransform;
}

Matrix4 SceneNode::GetWorldTransform()
{
	return worldTransform;
}

Mesh* SceneNode::GetMesh()
{
	if (mesh == NULL) {
		if (parent == NULL) {
			return NULL;
		}
		else {
			return parent->GetMesh();
		}
	}

	return mesh;
}

void SceneNode::SetMesh(Mesh* m)
{
	mesh = m;
}

Vector3 SceneNode::GetScale()
{
	return scale;
}

void SceneNode::SetScale(Vector3 sc)
{
	scale = sc;
}

void SceneNode::AddChildNode(SceneNode* s)
{
	children.push_back(s);
	s->parent = this;
	s->SetScale(s->GetScale() * scale);
	Update();
}

std::vector<SceneNode*> SceneNode::GetChildNodes()
{
	return children;
}

void SceneNode::Update()
{
	if (parent != NULL) { // If we have a parent
		worldTransform = parent->worldTransform * localTransform;
	}
	else { // If we are the root node
		worldTransform = localTransform;
	}

	// Cascade Update children
	for (SceneNode* child : children) {
		child->Update();
	}
}

void SceneNode::Draw()
{

	if (mesh != NULL) {
			Matrix4 scaleM = Matrix4::scaling(scale.getX(), scale.getY(), scale.getZ());
			float model[16];
			Matrix4 modelM = worldTransform * scaleM;
			mesh->setWorldTransform(modelM);
			mesh->Draw();
	}	
	// Cascade Draw children
	for (SceneNode* child : children) {
		child->Draw();
	}
}
