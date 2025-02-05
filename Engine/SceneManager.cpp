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
		//���ο� GameObject�� ������
		shared_ptr<GameObject> skyBox = make_shared<GameObject>();

		//Transform �߰�
		skyBox->AddComponent(make_shared<Transform>());
		
		//MeshFilter ������Ʈ�� skyBox GameObject�� �߰�
		shared_ptr<MeshFilter> meshFilter = make_shared<MeshFilter>();
		{
			//Sphere Mesh�� �ε��ϰ�
			shared_ptr<Mesh> sphereMesh = Resources::Get().LoadSphereMesh();
			
			//MeshFilter�� �ش� Sphere Mesh ����
			meshFilter->SetMesh(sphereMesh);
		}

		{
			//Shader�� Texture�� ����
			shared_ptr<Shader> shader = make_shared<Shader>();
			shared_ptr<Texture> texture = make_shared<Texture>();

			//Shader�� �ʱ�ȭ �ϰ� Rasterrizer  & Depth Stencil ����
			shader->Init(L"..\\Resources\\Shader\\SkyBox.fx", { RASTERRIZER_TYPE::CULL_NONE, DEPTH_STENCIL_TYPE::LESS_EQUAL});
			//Texture�� �ʱ�ȭ
			texture->Init(L"..\\Resources\\Texture\\kris-guico-rsB-he-ye7w-unsplash.jpg");

			//Material�� �����ϰ� Shader�� Texture�� ����
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);

			//Material�� MeshFilter�� ����
			meshFilter->SetMaterial(material);
		}

		//MeshFilter ������Ʈ�� skyBox GameObject�� �߰�
		skyBox->AddComponent(meshFilter);

		//skyBox�� ���� �߰�
		scene->AddGameObject(skyBox);
	}

#pragma endregion
				
#pragma region Sphere

	{
		shared_ptr<GameObject> sphere = make_shared<GameObject>();
		//���Ŀ� Transform �߰� �ϴ� ������
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
		//���Ŀ� Transform �߰� �ϴ� ������
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
		//���Ŀ� Transform �߰� �ϴ� ������
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
