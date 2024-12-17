#include "pch.h"
#include "MainGame.h"
#include <GameEngine.h>

shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();

void MainGame::Init(HWND hwnd, int width, int height, bool windowed)
{
	GameEngine::Get().Init(hwnd, width, height, windowed);

	//���� ������ �ʱ�ȭ(�ﰢ���� ����)
	vector<Vertex> vec(3);	//���� 3��
	vec[0].pos = XMFLOAT3(0.f, 0.5f, 0.5f);
	vec[0].color = XMFLOAT4(1.f, 0.f, 0.f, 1.f);//������ ����
	vec[1].pos = XMFLOAT3(0.5f, -0.5f, 0.5f);
	vec[1].color = XMFLOAT4(0.f, 1.f, 0.f, 1.f);//�ʷϻ� ����
	vec[2].pos = XMFLOAT3(-0.5f, -0.5f, 0.5f);
	vec[2].color = XMFLOAT4(0.f, 0.f, 1.f, 1.f);//�Ķ��� ����

	//�Ž� �ʱ�ȭ
	mesh->Init(vec);

	//���̴� �ʱ�ȭ
	shader->Init(L"..\\Resources\\Shader\\Default.hlsli");

	//��� ��⿭ ����ȭ ���
	GameEngine::Get().GetCmdQueue()->WaitSync();
}

void MainGame::Update()
{
	//������ ����
	GameEngine::Get().RenderBegin();

	//���̴� ������Ʈ
	shader->Update();

	//�Ž� ������
	mesh->Render();

	//������ ����
	GameEngine::Get().RenderEnd();
}
