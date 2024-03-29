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

std::vector<SceneGraph*> Scene::GetSceneGraphs()
{
	return sceneGraphs;
}

void Scene::SetupSceneGraph(SceneGraph* sceneGraph, Mesh meshes[])
{
	
	SceneNode* root = sceneGraph->AddNode();

	root->SetScale(Vector3(0.3f, 0.3f, 0.3f));
	root->SetPosition(Vector3(0.0f, -0.25f, 0.0f));
	root->SetRotation(Quaternion(45, Vector4(0.0f, 1.0f, 0.0f, 1.0f)));

	
	// FLOWER ////////////////////////////////////////////////////
	SceneNode* rose_base = sceneGraph->AddNode(NULL, root);
	rose_base->SetPosition(Vector3(0.0f, 2.25f, 0.0f));

	// Rose
	SceneNode* rose_flower = sceneGraph->AddNode(&meshes[0], rose_base);
	rose_flower->SetPosition(Vector3(-0.45f, 0.07f, 0.0f));
	//rose_flower->SetFrontCull(true);
	//rose_flower->SetBackCull(true);

	// Stem
	SceneNode* rose_stem = sceneGraph->AddNode(&meshes[1], rose_base);
	//////////////////////////////////////////////////////////////
	
	// BASE //////////////////////////////////////////////////////
	SceneNode* base = sceneGraph->AddNode(&meshes[3], root);
	base->SetPosition(Vector3(0.0f, -3.5f, 0.0f));
	//////////////////////////////////////////////////////////////
	
	// HANDLE ////////////////////////////////////////////////////
	SceneNode* handle = sceneGraph->AddNode(&meshes[4], root);
	handle->SetPosition(Vector3(0.0f, 6.0f, 0.0f));
	//handle->SetFrontCull(true);
	//handle->SetBackCull(true);
	//////////////////////////////////////////////////////////////
	
	// DOME //////////////////////////////////////////////////////
	
	SceneNode* dome_root = sceneGraph->AddNode(NULL, root);
	dome_root->SetRotation(Quaternion(90,Vector4(1,0,0,1)));
	dome_root->SetPosition(Vector3(0.0f, 3.0f, 0.0f));
	
	SceneNode* dome_back = sceneGraph->AddNode(&meshes[2], dome_root);
	dome_back->SetScale(Vector3(0.95f,0.95f,1.01f));
	dome_back->SetBackCull(false);
	dome_back->SetFrontCull(true);
	
	SceneNode* dome_front = sceneGraph->AddNode(&meshes[2], dome_root);
	dome_front->SetScale(Vector3(1.01f, 1.01f, 1.01f));
	dome_front->SetPosition(Vector3(0.0f, 0.0f, -0.2f));
	
	//////////////////////////////////////////////////////////////\
	

	//SceneNode* light = sceneGraph->AddNode(&meshes[5], root);
	//light->SetScale(Vector3(0.5, 0.5, 0.5));
	//light->SetPosition(Vector3(-6.0f, -2.0f, 4.0f));

	//SceneNode* cube1 = sceneGraph->AddNode(&meshes[4], root);
	
	//SceneNode* cube2 = sceneGraph->AddNode(&meshes[4], root);
	//cube2->SetScale(Vector3(0.25f, 4.0f, 8.0f));
	//cube2->SetPosition(Vector3(4.0f, 0.0f, 0.0f));

}

void Scene::ClearScene()
{
	sceneGraphs.clear();
}

void Scene::DrawSceneGraphs(bool ortho, bool drawLight)
{
	for (SceneGraph* sceneGraph : sceneGraphs) {
		sceneGraph->DrawSceneGraph(ortho, drawLight);
	}
}

void Scene::DrawSceneGraphsDepth(Shader* depthShader)
{
	for (SceneGraph* sceneGraph : sceneGraphs) {
		sceneGraph->DrawSceneGraphDepth(depthShader);
	}
}
