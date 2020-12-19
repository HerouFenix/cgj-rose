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
	root->ApplyLocalTransform(Matrix4::translation(0.0f, -1.8f, 0.0f));

	/*
	// FLOWER ////////////////////////////////////////////////////
	SceneNode* rose_base = sceneGraph->AddNode(NULL, root);
	rose_base->ApplyLocalTransform(Matrix4::translation(0.0f, 7.5f, 0.0f));
	rose_base->ApplyLocalTransform(Matrix4::rotationY(45, false));
	rose_base->ApplyLocalTransform(Matrix4::translation(0.08f, 0.0f, 0.18f));

	// Rose
	SceneNode* rose_flower = sceneGraph->AddNode(&meshes[0], rose_base);
	rose_flower->ApplyLocalTransform(Matrix4::translation(0.0f, 0.20f, 0.0f));

	
	// Stem
	SceneNode* rose_stem = sceneGraph->AddNode(&meshes[1], rose_base);
	rose_stem->ApplyLocalTransform(Matrix4::translation(0.36f, 0.0f, 0.0f));
	//////////////////////////////////////////////////////////////

	// BASE //////////////////////////////////////////////////////
	SceneNode* base = sceneGraph->AddNode(&meshes[3], root);
	base->ApplyLocalTransform(Matrix4::translation(0.0f, 1.5f, 0.0f));
	//////////////////////////////////////////////////////////////

	// HANDLE ////////////////////////////////////////////////////
	SceneNode* handle = sceneGraph->AddNode(&meshes[4], root);
	handle->ApplyLocalTransform(Matrix4::translation(0.0f, 11.2f, 0.0f));
	//////////////////////////////////////////////////////////////
	
	// DOME //////////////////////////////////////////////////////
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
	//////////////////////////////////////////////////////////////\
	*/
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
