#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

//�ʿ��Ѱ� �ҷ�����
#include "GameEngine.h"
#include "ConstantBuffer.h"
#include "Camera.h"
#include "Light.h"

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
	for (const shared_ptr<GameObject>& gameobject : gameObjects)
	{
		gameobject->FinalUpdate();
	}
}

void Scene::Render()
{
	//���� ������ Ǫ��
	PushLightData();

	//SceneManager���� ������� ���⼭
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetCamera() == nullptr)
			continue;

		gameObject->GetCamera()->Render();
	}
}

void Scene::PushLightData()
{
	//���� �Ķ���� ����ü �ʱ�ȭ null�� �б�
	LightParams lightParams = {};

	//���� ������Ʈ���� ��ȸ�ϸ鼭 ������ ������
	for (auto& gameObject : gameObjects)
	{
		//���� ������Ʈ�� ������ ������ ������ Ž��
		if (gameObject->GetLight() == nullptr)
			continue;

		//���� ������Ʈ�� ���� ������Ʈ�� ���� ������ ������
		const LightInfo& lightInfo = gameObject->GetLight()->GetLightInfo();

		//���� �Ķ���� ����ü�� ���� ������ �߰�
		lightParams.lights[lightParams.lightCount] = lightInfo;

		//���� ������ ����
		lightParams.lightCount++;

	}

	//��� ���ۿ� ���� ���� �����͸� Ǫ��
	GameEngine::Get().GetConstantBuffer(CONSTANT_BUFFER_TYPE::GLOBAL)->PushGlobalData(&lightParams, sizeof(lightParams));
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
