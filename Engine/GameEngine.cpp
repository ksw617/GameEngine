#include "pch.h"
#include "GameEngine.h"

void GameEngine::Init(HWND _hwnd, int _width, int _height, bool _windowed)
{
	hwnd = _hwnd;
	width = _width;
	height = _height;
	windowed = _windowed;

	ResizeWindow(_width, _height);
	viewPort = { 0,0, static_cast<FLOAT>(width), static_cast<FLOAT>(height), 0.0f, 1.0f };
	scissorRect = CD3DX12_RECT(0, 0, width, height);

	device = make_shared<Device>();
	commandQueue = make_shared<CommandQueue>();
	swapChain = make_shared<SwapChain>();
	rootSignature = make_shared<RootSignature>();

	//할당
	constBuffer = make_shared<ConstantBuffer>();

	device->Init();
	commandQueue->Init(device->GetDevice(), swapChain);
	swapChain->Init(hwnd, width, height, windowed, device->GetDevice(), device->GetDXGI(), commandQueue->GetCmdQueue());
	rootSignature->Init(device->GetDevice());

	//초기화
	constBuffer->Init(sizeof(XMFLOAT4), 256);
}


void GameEngine::Render()
{

	//RenderBegin();
	//
	////Todo : 나머지 물체 그려주기
	////추가적인 랜더링 로직을 여기에 작성
	//
	//RenderEnd();

}


void GameEngine::RenderBegin()
{
	commandQueue->RenderBegin(&viewPort, &scissorRect);
}

void GameEngine::RenderEnd()
{
	commandQueue->RenderEnd();
}

void GameEngine::ResizeWindow(int _width, int _height)
{
	width = _width;
	height = _height;

	RECT rect = { 0,0,width, height };

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(hwnd, 0, 100, 100, width, height, 0);
}
