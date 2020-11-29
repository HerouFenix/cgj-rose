#include "../../headers/scene/SceneNode.h"

Tetromino SceneNodeTetromino::getTetromino() {
	return tetromino;
}

SceneNodeTetromino::SceneNodeTetromino(Mesh* m, Shader* s, Tetromino t, Vector3 sc) :SceneNode(m, s, NULL, sc) {
	t.getColours(colour);
	tetromino = t;
}

SceneNodeTetromino::~SceneNodeTetromino()
{
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete  children[i];
	}
}

void SceneNodeTetromino::Draw()
{
	float colours[4];

	shader->Bind();
	tetromino.getColours(colours);

	shader->SetUniform4fvec("uniformColour", colours);
	shader->UnBind();

	Matrix4 scaleM = Matrix4::scaling(scale.getX(), scale.getY(), scale.getZ());

	//Draw each square that makes up the piece using the transform matrices
	for (int j = 0; j < 4; j++) {
		float model[16];
		Matrix4 modelM = worldTransform * scaleM * tetromino.getTransforms()[j];
		modelM.getRowMajor(model);
		Renderer::DrawObject((GLsizei)mesh->getVertices().size(), (*shader), model);
	}

	// Cascade Draw children
	for (SceneNode* child : children) {
		child->Draw();
	}
}
