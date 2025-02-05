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


	/*
#pragma region SkyBox
	
	{
		shared_ptr<GameObject> skyBox = make_shared<GameObject>();
		skyBox->AddComponent(make_shared<Transform>());

		//SkyBox는 CullingMask 적용안함
		skyBox->SetCullingMask(false);
		
		shared_ptr<MeshFilter> meshFilter = make_shared<MeshFilter>();
		{
			shared_ptr<Mesh> sphereMesh = Resources::Get().LoadSphereMesh();
			meshFilter->SetMesh(sphereMesh);
		}

		{
			shared_ptr<Shader> shader = make_shared<Shader>();
			shared_ptr<Texture> texture = make_shared<Texture>();

			shader->Init(L"..\\Resources\\Shader\\SkyBox.fx", { RASTERRIZER_TYPE::CULL_NONE, DEPTH_STENCIL_TYPE::LESS_EQUAL});
			texture->Init(L"..\\Resources\\Texture\\kris-guico-rsB-he-ye7w-unsplash.jpg");

			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshFilter->SetMaterial(material);
		}

		skyBox->AddComponent(meshFilter);
		scene->AddGameObject(skyBox);
	}

#pragma endregion
				
		   */
#pragma region Directional Light

	{
		shared_ptr<GameObject> light = make_shared<GameObject>();
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

#pragma region Sphere

	{
		shared_ptr<GameObject> sphere = make_shared<GameObject>();
		sphere->AddComponent(make_shared<Transform>());

		shared_ptr<Transform> transform = sphere->GetTransform();

		transform->SetLocalPosition(Vector3(0.f, 100.f, 200.f));
		transform->SetLocalScale(Vector3(100.f, 100.f, 100.f));


		shared_ptr<MeshFilter> meshFilter = make_shared<MeshFilter>();
		{
			shared_ptr<Mesh> mesh = Resources::Get().LoadCubeMesh();
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


#pragma region Sphere

	{
		shared_ptr<GameObject> sphere = make_shared<GameObject>();
		sphere->AddComponent(make_shared<Transform>());

		shared_ptr<Transform> transform = sphere->GetTransform();

		transform->SetLocalPosition(Vector3(100.f, 100.f, 200.f));
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

		camera->AddComponent(make_shared<Transform>());
		camera->AddComponent(make_shared<CameraMoveTest>());
		camera->AddComponent(make_shared<Camera>());

		camera->GetTransform()->SetLocalPosition(Vector3(0.f, 100.f, 0.f));

		scene->AddGameObject(camera);
	}

#pragma endregion





	
	return scene;
}
