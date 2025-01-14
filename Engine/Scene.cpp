#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

void Scene::Awake()
{
	//모든 GameObject의 Awake 함수 호출
	for(const shared_ptr<GameObject>& gameObject  : gameObjects)
	{
		gameObject->Awake();
	}
}

void Scene::Start()
{
	//모든 GameObject의 Start 함수 호출
	for (const shared_ptr<GameObject>& gameObject : gameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update()
{
	//모든 GameObject의 Update 함수 호출
	for (const shared_ptr<GameObject>& gameObject : gameObjects)
	{
		gameObject->Update();
	}
}

void Scene::LateUpdate()
{
	//모든 GameObject의 LateUpdate 함수 호출
	for (const shared_ptr<GameObject>& gameObject : gameObjects)
	{
		gameObject->LateUpdate();
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	//gameObjects에 추가
	gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	//gameObjects에서 해당 요소 제거
	auto findIt = find(gameObjects.begin(), gameObjects.end(), gameObject);
	if (findIt != gameObjects.end())
	{
		gameObjects.erase(findIt);
	}
}
