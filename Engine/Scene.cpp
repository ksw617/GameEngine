#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

void Scene::Awake()
{
	//��� GameObject�� Awake �Լ� ȣ��
	for(const shared_ptr<GameObject>& gameObject  : gameObjects)
	{
		gameObject->Awake();
	}
}

void Scene::Start()
{
	//��� GameObject�� Start �Լ� ȣ��
	for (const shared_ptr<GameObject>& gameObject : gameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update()
{
	//��� GameObject�� Update �Լ� ȣ��
	for (const shared_ptr<GameObject>& gameObject : gameObjects)
	{
		gameObject->Update();
	}
}

void Scene::LateUpdate()
{
	//��� GameObject�� LateUpdate �Լ� ȣ��
	for (const shared_ptr<GameObject>& gameObject : gameObjects)
	{
		gameObject->LateUpdate();
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	//gameObjects�� �߰�
	gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	//gameObjects���� �ش� ��� ����
	auto findIt = find(gameObjects.begin(), gameObjects.end(), gameObject);
	if (findIt != gameObjects.end())
	{
		gameObjects.erase(findIt);
	}
}
