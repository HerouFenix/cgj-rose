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

void Scene::SetupSceneGraph(SceneGraph* sceneGraph, Mesh meshes[])
{
	SceneNode* root = sceneGraph->AddNode();
	root->ApplyLocalTransform(Matrix4::scaling(0.3f, 0.3f, 0.3f)); 
	root->ApplyLocalTransform(Matrix4::translation(0.0f, -2.0f, 0.0f));

	// Rose
	SceneNode* rose = sceneGraph->AddNode(&meshes[0], root);
	//rose->ApplyLocalTransform(Matrix4::rotationX(90, false));
	rose->ApplyLocalTransform(Matrix4::translation(0.0f, 7.20f, 0.0f));

	
	// Stem
	SceneNode* stem = sceneGraph->AddNode(&meshes[1], root);
	//stem->ApplyLocalTransform(Matrix4::rotationX(90, false));
	stem->ApplyLocalTransform(Matrix4::translation(0.36f, 7.0f, 0.0f));

	// Base
	SceneNode* base = sceneGraph->AddNode(&meshes[3], root);
	//base->ApplyLocalTransform(Matrix4::rotationX(90, false));
	base->ApplyLocalTransform(Matrix4::translation(0.0f, 1.5f, 0.0f));

	// Handle
	SceneNode* handle = sceneGraph->AddNode(&meshes[4], root);
	handle->ApplyLocalTransform(Matrix4::translation(0.0f, 11.2f, 0.0f));

	
	// Dome
	//SceneNode* dome = sceneGraph->AddNode(NULL, root);
	//dome->ApplyLocalTransform(Matrix4::translation(0.0f, 1.65f, 0.0f));
	//
	//SceneNode* domeQuarter1 = sceneGraph->AddNode(&meshes[2], dome);
	//
	//SceneNode* domeQuarter2 = sceneGraph->AddNode(&meshes[2], dome);
	//domeQuarter2->ApplyLocalTransform(Matrix4::rotationY(90, false));
	//
	//SceneNode* domeQuarter3 = sceneGraph->AddNode(&meshes[2], dome);
	//domeQuarter3->ApplyLocalTransform(Matrix4::rotationY(180, false));
	//
	//SceneNode* domeQuarter4 = sceneGraph->AddNode(&meshes[2], dome);
	//domeQuarter4->ApplyLocalTransform(Matrix4::rotationY(270, false));

	SceneNode* dome_root = sceneGraph->AddNode(NULL, root);
	dome_root->ApplyLocalTransform(Matrix4::rotationX(90, false));

	SceneNode* dome_back = sceneGraph->AddNode(&meshes[2], dome_root);
	dome_back->ApplyLocalTransform(Matrix4::scaling(0.95,0.95,1.01));
	dome_back->ApplyLocalTransform(Matrix4::translation(0.0f, 0.0f, -8.1f));
	dome_back->SetDrawFaceCulling(true, false);

	SceneNode* dome_front = sceneGraph->AddNode(&meshes[2], dome_root);
	dome_front->ApplyLocalTransform(Matrix4::scaling(1.01, 1.01, 1.01));
	dome_front->ApplyLocalTransform(Matrix4::translation(0.0f, 0.0f, -8.28f));
	dome_front->SetDrawFaceCulling(true, true);

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
