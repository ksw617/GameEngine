#include "pch.h"
#include "GameEngine.h"
#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h"

//���� �ʱ�ȭ �Լ� : ������ �ڵ�, ȭ�� �ʺ�, ����, â ��� ���θ� ���ڷ� ����
void GameEngine::Init(HWND _hwnd, int _width, int _height, bool _windowed)
{
	//���ڷ� ���� ���� ��� ������ ����
	hwnd = _hwnd;
	width = _width;
	height = _height;
	windowed = _windowed;

	//������ ũ�� ����
	ResizeWindow(_width, _height);

	//�׷��� ȭ���� ����Ʈ ����
	viewPort = { 0,0, static_cast<FLOAT>(width), static_cast<FLOAT>(height), 0.0f, 1.0f };

	//����(RECT) ����
	scissorRect = CD3DX12_RECT(0, 0, width, height);

	//Device, CommandQueue, SwapChain ��ü�� ������ ����Ʈ �����Ϳ� ����
	device = make_shared<Device>();
	commandQueue = make_shared<CommandQueue>();
	swapChain = make_shared<SwapChain>();

	//device �ʱ�ȭ
	device->Init();

	//CommandQueue �ʱ�ȭ(Device, SwapChain) ����
	commandQueue->Init(device->GetDevice(), swapChain);

	//SwapChain �ʱ�ȭ(������ �ڵ�, �ʺ�, ����, â ���, Device, DXGI ���丮, CommandQueue)
	swapChain->Init(hwnd, width, height, windowed, device->GetDevice(), device->GetDXGI(), commandQueue->GetCmdQueue());
}

//������ �Լ� : ������ ���۰� ���� ����
void GameEngine::Render()
{
	//������ ����
	RenderBegin();

	//Todo : ������ ��ü �׷��ֱ�
	//�߰����� ������ ������ ���⿡ �ۼ�

	//������ ����
	RenderEnd();

}

//������ ���� �Լ� : �������� �ʿ��� �ʱ� ������ ����
void GameEngine::RenderBegin()
{
	//commandQueue�� RenderBigin ȣ��(����Ʈ, ���� ����)
	commandQueue->RenderBegin(&viewPort, &scissorRect);
}

//������ ���� �Լ� : ������ �� �ʿ��� ������ �۾��� ����
void GameEngine::RenderEnd()
{
	//commandQueue�� RenderEnd ȣ��
	commandQueue->RenderEnd();
}

void GameEngine::ResizeWindow(int _width, int _height)
{
	//���ο� �ʺ�� ���̸� ��� ������ ���� 
	width = _width;
	height = _height;

	//������ ũ�⸦ �����ϱ� ���� RECT ����ü ����
	RECT rect = { 0,0,width, height };

	//������ ũ�� ����
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//������ ��ġ�� ũ�� ����
	SetWindowPos(hwnd, 0, 100, 100, width, height, 0);
}
