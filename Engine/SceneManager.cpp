#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameEngine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshFilter.h"
#include "Camera.h" 
#include "Transform.h"  // 호출

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

	//gameObject에서 Transform 가져와서
	shared_ptr<Transform> transform = gameObject->GetTransform();

	//transform 위치값 설정
	transform->SetLocalPosition(Vector3(0.f, 100.f, 200.f));

	//tranform의 크기값 설정
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

	//새로운 게임 객체를 생성(카메라 역할)
	shared_ptr<GameObject> camera = make_shared<GameObject>();

	//Transform 컴포넌트를 추가(위치, 회전, 스케일 정보를 관리)
	camera->AddComponent(make_shared<Transform>());

	//Camera 컴포넌트를 추가(near = 0.3f, far = 1000.f, Fov = 45도)
	camera->AddComponent(make_shared<Camera>());

	//카메라 위치를 설정(로컬 좌표계에서(0f, 100f, 0f) 위치로 설정)
	camera->GetTransform()->SetLocalPosition(Vector3(0.f, 100.f, 0.f));

	//카메라 객체를 씬에 추가
	testScene->AddGameObject(camera);

	return testScene;
}
