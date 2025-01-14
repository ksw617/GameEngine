#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

//�߰�
#include "GameEngine.h"
#include "Material.h"

#include "GameObject.h"
#include "MeshFilter.h"


void SceneManager::LoadScene(wstring sceneName)
{
	//Test��
	currentScene = LoadTestScene();

	currentScene->Awake();
	currentScene->Start();
}


void SceneManager::Update()
{
	if (currentScene != nullptr)
	{	  
		currentScene->Update();
		currentScene->LateUpdate();
	}
}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
	//�׽�Ʈ�� �� �����
	shared_ptr<Scene> testScene = make_shared<Scene>();//Test scene �����

	//�׽�Ʈ�� ���ӿ�����Ʈ �����
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

	//�׽�Ʈ�� ���ӿ�����Ʈ�� meshFilter �߰�
	gameObject->AddComponent(meshFilter);

	//�׽�Ʈ�� �����ٰ� gameObject �߰�
	testScene->AddGameObject(gameObject);

	//�׽�Ʈ�� �� ��ȯ
	return testScene;
}
