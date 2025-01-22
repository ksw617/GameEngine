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
#include "Resources.h" // Resources 호출

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




	
#pragma region Sphere

	{
		//Sphere 오브젝트 생성
		shared_ptr<GameObject> sphere = make_shared<GameObject>();
		sphere->Init();

		shared_ptr<Transform> transform = sphere->GetTransform();

		//위치만 조금 바꿈
		transform->SetLocalPosition(Vector3(0.f, 100.f, 200.f));
		transform->SetLocalScale(Vector3(100.f, 100.f, 100.f));


		shared_ptr<MeshFilter> meshFilter = make_shared<MeshFilter>();

		{
			//Resources에서 Sphere Mesh 로드및 생성
			shared_ptr<Mesh> mesh = Resources::Get().LoadSphereMesh();
			meshFilter->SetMesh(mesh);
		}
		{
			shared_ptr<Shader> shader = make_shared<Shader>();
			shared_ptr<Texture> texture = make_shared<Texture>();

			shader->Init(L"..\\Resources\\Shader\\Default.hlsli");
			texture->Init(L"..\\Resources\\Texture\\DirectX.png");


			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshFilter->SetMaterial(material);
		}

		sphere->AddComponent(meshFilter);
		scene->AddGameObject(sphere);

	}
	
#pragma endregion


#pragma region Camera

	{
		shared_ptr<GameObject> camera = make_shared<GameObject>();

		camera->AddComponent(make_shared<Transform>());
		camera->AddComponent(make_shared<CameraMoveTest>());
		camera->AddComponent(make_shared<Camera>());
		camera->GetTransform()->SetLocalPosition(Vector3(0.f, 100.f, 0.f));

		scene->AddGameObject(camera);
	}

#pragma endregion


	return scene;
}
