#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameEngine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshFilter.h"
#include "Camera.h" 
#include "Transform.h"  
#include "CameraMoveTest.h" // test �߰�

void SceneManager::LoadScene(wstring sceneName)
{
	currentScene = LoadSampleScene();

	currentScene->Awake();
	currentScene->Start();
}


void SceneManager::Update()
{
	if (currentScene != nullptr)
	{	  
		currentScene->Update();
		currentScene->LateUpdate();
		currentScene->FinalUpdate();
	}
}

void SceneManager::Render()
{

	if (currentScene == nullptr)
		return;

	const vector<shared_ptr<GameObject>>& gameObjects = currentScene->GetGameObjets();

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetCamera() == nullptr)
			continue;

		gameObject->GetCamera()->Render();
	}


}

shared_ptr<Scene> SceneManager::LoadSampleScene()
{
	shared_ptr<Scene> testScene = make_shared<Scene>();
	shared_ptr<GameObject> gameObject = make_shared<GameObject>();

	vector<Vertex> vec(4);
	vec[0].pos = XMFLOAT3(-0.5f, 0.5f, 0.5f);
	vec[0].color = XMFLOAT4(1.f, 0.f, 0.f, 1.f);
	vec[0].uv = XMFLOAT2(0.f, 0.f);
	vec[1].pos = XMFLOAT3(0.5f, 0.5f, 0.5f);
	vec[1].color = XMFLOAT4(0.f, 1.f, 0.f, 1.f);
	vec[1].uv = XMFLOAT2(1.f, 0.f);
	vec[2].pos = XMFLOAT3(0.5f, -0.5f, 0.5f);
	vec[2].color = XMFLOAT4(0.f, 0.f, 1.f, 1.f);
	vec[2].uv = XMFLOAT2(1.f, 1.f);
	vec[3].pos = XMFLOAT3(-0.5f, -0.5f, 0.5f);
	vec[3].color = XMFLOAT4(0.f, 1.f, 0.f, 1.f);
	vec[3].uv = XMFLOAT2(0.f, 1.f);


	vector<UINT32> indexVertex;
	indexVertex.push_back(0);
	indexVertex.push_back(1);
	indexVertex.push_back(2);

	indexVertex.push_back(0);
	indexVertex.push_back(2);
	indexVertex.push_back(3);

	gameObject->Init();

	shared_ptr<Transform> transform = gameObject->GetTransform();
	transform->SetLocalPosition(Vector3(0.f, 100.f, 200.f));
	transform->SetLocalScale(Vector3(100.f, 100.f, 1.f));

	shared_ptr<MeshFilter> meshFilter = make_shared<MeshFilter>();

	{
		shared_ptr<Mesh> mesh = make_shared<Mesh>();
		mesh->Init(vec, indexVertex);
		meshFilter->SetMesh(mesh);
	}

	{

		shared_ptr<Shader> shader = make_shared<Shader>();
		shared_ptr<Texture> texture = make_shared<Texture>();

		shader->Init(L"..\\Resources\\Shader\\Default.hlsli");
		texture->Init(L"..\\Resources\\Texture\\DirectX.png");

		shared_ptr<Material> material = make_shared<Material>();

		material->SetShader(shader);
		material->SetFloat(0, 0.1f);
		material->SetFloat(1, 0.3f);
		material->SetFloat(2, 0.4f);
		material->SetTexture(0, texture);

		meshFilter->SetMaterial(material);

	}

	gameObject->AddComponent(meshFilter);
	testScene->AddGameObject(gameObject);

	shared_ptr<GameObject> camera = make_shared<GameObject>();

	camera->AddComponent(make_shared<Transform>());
	//ī�޶� �������ִ� Ŀ���� ������Ʈ�� ī�޶� ����
	camera->AddComponent(make_shared<CameraMoveTest>());

	camera->AddComponent(make_shared<Camera>());
	camera->GetTransform()->SetLocalPosition(Vector3(0.f, 100.f, 0.f));

	testScene->AddGameObject(camera);

	return testScene;
}
