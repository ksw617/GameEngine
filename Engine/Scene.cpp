#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

void Scene::Awake()
{
	for(const shared_ptr<GameObject>& gameObject  : gameObjects)
	{
		gameObject->Awake();
	}
}

void Scene::Start()
{
	for (const shared_ptr<GameObject>& gameObject : gameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update()
{
	for (const shared_ptr<GameObject>& gameObject : gameObjects)
	{
		gameObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (const shared_ptr<GameObject>& gameObject : gameObjects)
	{
		gameObject->LateUpdate();
	}
}

void Scene::FinalUpdate()
{
	//��� GameObject�� FinalUpdate �Լ� ȣ��
	for (const shared_ptr<GameObject>& gameobject : gameObjects)
	{
		gameobject->FinalUpdate();
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	auto findIt = find(gameObjects.begin(), gameObjects.end(), gameObject);
	if (findIt != gameObjects.end())
	{
		gameObjects.erase(findIt);
	}
}
