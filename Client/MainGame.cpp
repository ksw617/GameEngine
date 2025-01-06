#include "pch.h"
#include "MainGame.h"
#include <GameEngine.h>
#include <Material.h>  // Material추가

shared_ptr<Mesh> mesh = make_shared<Mesh>();
//쉐이더랑 Texture Matreial을 통해 처리
//shared_ptr<Shader> shader = make_shared<Shader>();
//shared_ptr<Texture> texture = make_shared<Texture>(); 

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

	mesh->Init(vec, indexVertex);

	//로컬에다가
	shared_ptr<Shader> shader = make_shared<Shader>();
	shared_ptr<Texture> texture = make_shared<Texture>();

	shader->Init(L"..\\Resources\\Shader\\Default.hlsli");
	texture->Init(L"..\\Resources\\Texture\\DirectX.png");

	//Material 추가
	shared_ptr<Material> material = make_shared<Material>();
	//초기화
	material->SetShader(shader);
	material->SetFloat(0, 0.1f);
	material->SetFloat(1, 0.3f);
	material->SetFloat(2, 0.4f);
	material->SetTexture(0, texture);
	mesh->SetMaterial(material);

	GameEngine::Get().GetCmdQueue()->WaitSync();
}

void MainGame::Update()
{
	GameEngine::Get().RenderBegin();
	GameEngine::Get().Update();

	//제거
	//shader->Update();

	{
		static XMFLOAT4 transform = {};
		float deltaTime = GameEngine::Get().GetTimer()->GetDeltaTime();

		if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::W))
		{
			transform.y += 1.f * deltaTime;
		}

		if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::S))
		{
			transform.y -= 1.f * deltaTime;
		}

		if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::A))
		{
			transform.x -= 1.f * deltaTime;
		}

		if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::D))
		{
			transform.x += 1.f * deltaTime;
		}

		
		mesh->SetTransform(transform);

		//제거
		//mesh->SetTexture(texture);

		mesh->Render();
	}

	GameEngine::Get().RenderEnd();
}
