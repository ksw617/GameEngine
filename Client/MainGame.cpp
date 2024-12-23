#include "pch.h"
#include "MainGame.h"
#include <GameEngine.h>

shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();

void MainGame::Init(HWND hwnd, int width, int height, bool windowed)
{
	GameEngine::Get().Init(hwnd, width, height, windowed);

	//정점 4개를 사용하여 사각형 그리기
	vector<Vertex> vec(4);	
	vec[0].pos = XMFLOAT3(-0.5f, 0.5f, 0.5f);
	vec[0].color = XMFLOAT4(1.f, 0.f, 0.f, 1.f);
	vec[1].pos = XMFLOAT3(0.5f, 0.5f, 0.5f);
	vec[1].color = XMFLOAT4(0.f, 1.f, 0.f, 1.f);
	vec[2].pos = XMFLOAT3(0.5f, -0.5f, 0.5f);
	vec[2].color = XMFLOAT4(0.f, 0.f, 1.f, 1.f);
	vec[3].pos = XMFLOAT3(-0.5f, -0.5f, 0.5f);
	vec[3].color = XMFLOAT4(0.f, 1.f, 0.f, 1.f);


	//인덱스 정점 설정
	vector<UINT32> indexVertex;
	indexVertex.push_back(0);
	indexVertex.push_back(1);
	indexVertex.push_back(2);

	indexVertex.push_back(0);
	indexVertex.push_back(2);
	indexVertex.push_back(3);

	//초기화
	mesh->Init(vec, indexVertex);

	shader->Init(L"..\\Resources\\Shader\\Default.hlsli");

	GameEngine::Get().GetCmdQueue()->WaitSync();
}

void MainGame::Update()
{
	GameEngine::Get().RenderBegin();

	shader->Update();

	//위치 설정
	{
		XMFLOAT4 transform(0.f, 0.f, 0.f, 0.f);
		mesh->SetTransform(transform);

		mesh->Render();
	}

	GameEngine::Get().RenderEnd();
}
