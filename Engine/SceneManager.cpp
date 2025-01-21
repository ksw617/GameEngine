#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameEngine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshFilter.h"
#include "Camera.h" 
#include "Transform.h"  
#include "CameraMoveTest.h"
#include "Resources.h" // Resources ȣ��

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
	shared_ptr<Scene> scene = make_shared<Scene>();


#pragma region Cube

	//Cube ������Ʈ ����
	shared_ptr<GameObject> cube = make_shared<GameObject>();
	cube->Init();

	shared_ptr<Transform> transform = cube->GetTransform();

	transform->SetLocalPosition(Vector3(150.f, 100.f, 200.f));	  //��ġ��
	transform->SetLocalScale(Vector3(100.f, 100.f, 100.f));		  //ũ�Ⱚ


	shared_ptr<MeshFilter> meshFilter = make_shared<MeshFilter>();

	{
		//Resources���� Cube Mesh �ε�� ����
		shared_ptr<Mesh> mesh = Resources::Get().LoadCubeMesh();
		meshFilter->SetMesh(mesh);
	}
	{
		//Shader �� Texture �ε�
		shared_ptr<Shader> shader = make_shared<Shader>();
		shared_ptr<Texture> texture = make_shared<Texture>();

		shader->Init(L"..\\Resources\\Shader\\Default.hlsli");
		texture->Init(L"..\\Resources\\Texture\\DirectX.png");

		//Material  ���� �� ����
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);		// ���̴� ����
		material->SetTexture(0, texture);	// �ؽ�ó ����
		meshFilter->SetMaterial(material);	//MeshFilter�� Material ����
	}

	//Cube ������Ʈ�� MeshFilter ������Ʈ �߰�
	cube->AddComponent(meshFilter);
	//scene�� Cube ������Ʈ �߰�
	scene->AddGameObject(cube);


#pragma endregion


#pragma region Camera
	shared_ptr<GameObject> camera = make_shared<GameObject>();

	camera->AddComponent(make_shared<Transform>());
	camera->AddComponent(make_shared<CameraMoveTest>());
	camera->AddComponent(make_shared<Camera>());
	camera->GetTransform()->SetLocalPosition(Vector3(0.f, 100.f, 0.f));

	scene->AddGameObject(camera);

	return scene;
#pragma endregion




}
