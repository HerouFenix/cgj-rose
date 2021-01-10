#include "../../headers/scene/SceneNode.h"

SceneNode::SceneNode(Mesh* m, SceneNode* parent_node) {
	mesh = m;
	parent = parent_node;
	scale = Vector3(1, 1, 1);
	position = Vector3(0, 0, 0);
	rotation = Quaternion();
}

SceneNode::SceneNode() {
	scale = Vector3(1, 1, 1);
	position = Vector3(0, 0, 0);
	rotation = Quaternion();
}


SceneNode::~SceneNode()
{
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete  children[i];
	}
}


void SceneNode::ResetToDefault() {
	scale = Vector3(1, 1, 1);
	position = Vector3(0, 0, 0);
	rotation = Quaternion();
}

Matrix4 SceneNode::GetLocalTransform()
{
	Matrix4 transform = Matrix4::identity();
	transform = transform.translation(position) * rotation.GLRotationMatrix() * transform.scaling(scale);
	return transform;
}

Matrix4 SceneNode::GetWorldTransform()
{
	if (parent != NULL) { // If we have a parent
		return parent->GetWorldTransform() * GetLocalTransform();
	}

	return GetLocalTransform();
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


void SceneNode::SetScale(Vector3 sc)
{
	scale = sc;
}

void SceneNode::SetPosition(Vector3 pos)
{
	position = pos;
}


void SceneNode::SetRotation(Quaternion rot)
{
	rotation = rot;
}

void SceneNode::AddChildNode(SceneNode* s)
{
	children.push_back(s);
	s->parent = this;
}

std::vector<SceneNode*> SceneNode::GetChildNodes()
{
	return children;
}

void SceneNode::SetBackCull(bool cull) {
	backCull = cull;
}

void SceneNode::SetFrontCull(bool cull) {
	frontCull = cull;
}


void SceneNode::PreDraw() {
	if (frontCull) {
		glCullFace(GL_FRONT);
	}
	else if (backCull) {
		glCullFace(GL_BACK);
	}else { //If neither front nor face culling, disable culling
		glDisable(GL_CULL_FACE);
		cullDisabled = true;
	}
}

void SceneNode::PostDraw() {
	if (cullDisabled) { //Reenable culling
		glEnable(GL_CULL_FACE);
		cullDisabled = false;
	}
}

void SceneNode::Draw()
{
	if (mesh != NULL) {
		Matrix4 modelM = GetWorldTransform();
		mesh->setWorldTransform(modelM);

		PreDraw();
		mesh->Draw();
		PostDraw();
	}
	// Cascade Draw children
	for (SceneNode* child : children) {
		child->Draw();
	}
}

void SceneNode::DrawDepth(Shader* depthShader)
{
	if (mesh != NULL && !mesh->material->transparent) {
		Matrix4 modelM = GetWorldTransform();
		mesh->setWorldTransform(modelM);

		PreDraw();
		mesh->DrawDepth(depthShader);
		PostDraw();
	}
	// Cascade Draw children
	for (SceneNode* child : children) {
		child->DrawDepth(depthShader);
	}
}