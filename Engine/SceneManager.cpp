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
#include "Resources.h" 
#include "Light.h"

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
	if (currentScene != nullptr)
		currentScene->Render();
}

shared_ptr<Scene> SceneManager::LoadSampleScene()
{
	shared_ptr<Scene> scene = make_shared<Scene>();


#pragma region SkyBox
	
	{
		//새로운 GameObject를 생성함
		shared_ptr<GameObject> skyBox = make_shared<GameObject>();

		//Transform 추가
		skyBox->AddComponent(make_shared<Transform>());
		
		//MeshFilter 컴포넌트를 skyBox GameObject에 추가
		shared_ptr<MeshFilter> meshFilter = make_shared<MeshFilter>();
		{
			//Sphere Mesh를 로드하고
			shared_ptr<Mesh> sphereMesh = Resources::Get().LoadSphereMesh();
			
			//MeshFilter에 해당 Sphere Mesh 설정
			meshFilter->SetMesh(sphereMesh);
		}

		{
			//Shader와 Texture를 생성
			shared_ptr<Shader> shader = make_shared<Shader>();
			shared_ptr<Texture> texture = make_shared<Texture>();

			//Shader를 초기화 하고 Rasterrizer  & Depth Stencil 설정
			shader->Init(L"..\\Resources\\Shader\\SkyBox.fx", { RASTERRIZER_TYPE::CULL_NONE, DEPTH_STENCIL_TYPE::LESS_EQUAL});
			//Texture를 초기화
			texture->Init(L"..\\Resources\\Texture\\kris-guico-rsB-he-ye7w-unsplash.jpg");

			//Material을 생성하고 Shader와 Texture를 설정
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);

			//Material을 MeshFilter에 설정
			meshFilter->SetMaterial(material);
		}

		//MeshFilter 컴포넌트를 skyBox GameObject에 추가
		skyBox->AddComponent(meshFilter);

		//skyBox를 씬에 추가
		scene->AddGameObject(skyBox);
	}

#pragma endregion
				
#pragma region Sphere

	{
		shared_ptr<GameObject> sphere = make_shared<GameObject>();
		//추후에 Transform 추가 하는 쪽으로
		sphere->AddComponent(make_shared<Transform>());

		shared_ptr<Transform> transform = sphere->GetTransform();

		transform->SetLocalPosition(Vector3(0.f, 100.f, 200.f));
		transform->SetLocalScale(Vector3(100.f, 100.f, 100.f));


		shared_ptr<MeshFilter> meshFilter = make_shared<MeshFilter>();
		{
			shared_ptr<Mesh> mesh = Resources::Get().LoadSphereMesh();
			meshFilter->SetMesh(mesh);
		}
		{
			shared_ptr<Shader> shader = make_shared<Shader>();
			shared_ptr<Texture> texture = make_shared<Texture>();
			shared_ptr<Texture> normalMap = make_shared<Texture>();

			shader->Init(L"..\\Resources\\Shader\\Default.fx");
			texture->Init(L"..\\Resources\\Texture\\Stylized_Stone_Floor_010_basecolor.png");
			normalMap->Init(L"..\\Resources\\Texture\\Stylized_Stone_Floor_010_normal.png");



			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			material->SetTexture(1, normalMap);
			meshFilter->SetMaterial(material);
		}

		sphere->AddComponent(meshFilter);
		scene->AddGameObject(sphere);

	}
	
#pragma endregion
			
#pragma region Camera

	{
		shared_ptr<GameObject> camera = make_shared<GameObject>();
		//추후에 Transform 추가 하는 쪽으로
		camera->AddComponent(make_shared<Transform>());

		camera->AddComponent(make_shared<Transform>());
		camera->AddComponent(make_shared<CameraMoveTest>());
		camera->AddComponent(make_shared<Camera>());
		camera->GetTransform()->SetLocalPosition(Vector3(0.f, 100.f, 0.f));

		scene->AddGameObject(camera);
	}

#pragma endregion




#pragma region Directional Light

	{
		shared_ptr<GameObject> light = make_shared<GameObject>();
		//추후에 Transform 추가 하는 쪽으로
		light->AddComponent(make_shared<Transform>());

		light->AddComponent(make_shared<Light>());
		light->GetLight()->SetLightType(LIGHT_TYPE::DIRECTIONAL_LIGHT);
		light->GetLight()->SetLightDirection(Vector3(1.f, -1.f, 1.f));
		light->GetLight()->SetDiffuse(Vector3(0.7f, 0.7f, 0.7f));
		light->GetLight()->SetAmbient(Vector3(0.3f, 0.3f, 0.3f));
		light->GetLight()->SetSpecular(Vector3(0.3f, 0.3f, 0.3f));

		scene->AddGameObject(light);
	}

#pragma endregion

	
	return scene;
}
