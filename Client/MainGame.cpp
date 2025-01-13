#include "pch.h"
#include "MainGame.h"
#include <GameEngine.h>
#include <Material.h> 

//Mesh 제거
//shared_ptr<Mesh> mesh = make_shared<Mesh>();

#include <GameObject.h> // GameObject 추가 
#include <MeshFilter.h>	// MeshFilter 추가

// 대신에 GameObject 만듬
shared_ptr<GameObject> gameObject = make_shared<GameObject>();

void MainGame::Init(HWND hwnd, int width, int height, bool windowed)
{
	GameEngine::Get().Init(hwnd, width, height, windowed);

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

	//mesh->Init(vec, indexVertex);
	//GameObject 초기화 호출 Transform 할당
	gameObject->Init();

	//meshFilter 만들어 주고
	shared_ptr<MeshFilter> meshFilter = make_shared<MeshFilter>();

	{
		//mesh를 여기다 만들어 줄꺼임
		shared_ptr<Mesh> mesh = make_shared<Mesh>();
		//mesh초기화
		mesh->Init(vec, indexVertex);

		//meshFilter에 mesh 추가
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

		//MeshFilter에 Material추가
		meshFilter->SetMaterial(material);

	}

	//gameObject에 MeshFilter 컴퍼넌트 추가
	gameObject->AddComponent(meshFilter);

	GameEngine::Get().GetCmdQueue()->WaitSync();
}

void MainGame::Update()
{
	GameEngine::Get().RenderBegin();
	GameEngine::Get().Update();

	//gameObject 업데이트 실행
	gameObject->Update();

	GameEngine::Get().RenderEnd();
}
