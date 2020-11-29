#include "../../headers/scene/SceneNode.h"


SceneNode::SceneNode(Mesh* m, Shader* s, float* c, Vector3 sc) {
	mesh = m;
	if (c == NULL) {
		float r = (float)(rand() % 256) / 255;
		float g = (float)(rand() % 256) / 255;
		float b = (float)(rand() % 256) / 255;

		colour[0] = r;
		colour[1] = g;
		colour[2] = b;
		colour[3] = 1.0f;
	}
	else {
		colour[0] = c[0];
		colour[1] = c[1];
		colour[2] = c[2];
		colour[3] = c[3];
	}

	parent = NULL;
	shader = s;
	scale = sc;

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

void SceneNode::GetColour(float* colours)
{
	colours[0] = colour[0];
	colours[1] = colour[1];
	colours[2] = colour[2];
	colours[3] = colour[3];
}

void SceneNode::SetColour(float* colours)
{
	colour[0] = colours[0];
	colour[1] = colours[1];
	colour[2] = colours[2];
	colour[3] = colours[3];
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

Shader* SceneNode::GetShader()
{
	if (shader == NULL) {
		if (parent == NULL) {
			return NULL;
		}
		else {
			return parent->GetShader();
		}
	}

	return shader;
}

void SceneNode::SetShader(Shader* s)
{
	shader = s;
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
	Shader* sh = GetShader();
	Mesh* me = GetMesh();

	if (sh != NULL && me != NULL) {
		sh->Bind();

		sh->SetUniform4fvec("uniformColour", colour);
		sh->UnBind();


		Matrix4 scaleM = Matrix4::scaling(scale.getX(), scale.getY(), scale.getZ());

		float model[16];
		Matrix4 modelM = worldTransform * scaleM;
		modelM.getRowMajor(model);
		Renderer::DrawObject((GLsizei)me->getVertices().size(), (*sh), model);
	}


	// Cascade Draw children
	for (SceneNode* child : children) {
		child->Draw();
	}
}
