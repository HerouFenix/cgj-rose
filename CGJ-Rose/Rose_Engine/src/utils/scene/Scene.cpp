#include "../../headers/scene/Scene.h"

Scene::Scene()
{
	srand((unsigned int)time(0));
}

SceneGraph* Scene::CreateSceneGraph()
{
	SceneGraph* newSceneGraph = new SceneGraph();
	sceneGraphs.push_back(newSceneGraph);

	return newSceneGraph;
}

SceneGraph* Scene::CreateSceneGraph(ArcBallCamera c)
{
	SceneGraph* newSceneGraph = new SceneGraph(c);
	sceneGraphs.push_back(newSceneGraph);

	return newSceneGraph;
}

std::vector<SceneGraph*> Scene::GetSceneGraphs()
{
	return sceneGraphs;
}

void Scene::SetupSceneGraph(SceneGraph* sceneGraph, Mesh meshes[], Shader* s)
{
	SceneNode* root = sceneGraph->AddNode();
	root->ApplyLocalTransform(Matrix4::scaling(0.4f, 0.4f, 0.4f)); 
	root->ApplyLocalTransform(Matrix4::translation(0.0f, -2.0f, 0.0f));

	// Rose
	SceneNode* rose = sceneGraph->AddNode(&meshes[0], s, root);
	rose->ApplyLocalTransform(Matrix4::rotationX(90, false));
	rose->ApplyLocalTransform(Matrix4::translation(0.0f, 2.20f, 0.0f));
	rose->SetColour(new float[] {0.7f, 0.0f, 1.0f});

	// Stem
	SceneNode* stem = sceneGraph->AddNode(&meshes[1], s, root);
	stem->ApplyLocalTransform(Matrix4::rotationX(90, false));
	stem->ApplyLocalTransform(Matrix4::translation(0.3f, 0.2f, 0.0f));
	stem->SetColour(new float[] {0.5f, 0.9f, 0.3f});

	// Dome
	SceneNode* dome = sceneGraph->AddNode(&meshes[2], s, root);
	dome->ApplyLocalTransform(Matrix4::rotationX(90, false));
	dome->ApplyLocalTransform(Matrix4::translation(0.0f, 13.0f, 0.0f));
	dome->SetColour(new float[] {0.6f, 1.0f, 0.9f});

	// Base
	SceneNode* base = sceneGraph->AddNode(&meshes[3], s, root);
	base->ApplyLocalTransform(Matrix4::rotationX(90, false));
	base->ApplyLocalTransform(Matrix4::translation(0.0f, -4.0f, 0.0f));
	base->SetColour(new float[] {0.7f, 0.3f, 0.0f});

	// Handle
	SceneNode* handle = sceneGraph->AddNode(&meshes[4], s, root);
	handle->ApplyLocalTransform(Matrix4::translation(0.0f, 15.5f, 0.0f));
	handle->SetColour(new float[] {0.7f, 0.3f, 0.0f});
}

void Scene::ClearScene()
{
	sceneGraphs.clear();
}

void Scene::DrawSceneGraphs(bool ortho)
{
	for (SceneGraph* sceneGraph : sceneGraphs) {
		sceneGraph->DrawSceneGraph(ortho);
	}
}
