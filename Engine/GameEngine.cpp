#include "pch.h"
#include "GameEngine.h"

void GameEngine::Init(HWND _hwnd, int _width, int _height, bool _windowed)
{
	hwnd = _hwnd;
	width = _width;
	height = _height;
	windowed = _windowed;

	viewPort = { 0,0, static_cast<FLOAT>(width), static_cast<FLOAT>(height), 0.0f, 1.0f };
	scissorRect = CD3DX12_RECT(0, 0, width, height);

	device = make_shared<Device>();
	commandQueue = make_shared<CommandQueue>();
	swapChain = make_shared<SwapChain>();
	rootSignature = make_shared<RootSignature>();
	constBuffer = make_shared<ConstantBuffer>();
	tableDesc = make_shared<TableDescriptor>();
	depthStencilBuffer = make_shared<DepthStencilBuffer>(); 	
	input = make_shared<Input>();

	timer = make_shared<Timer>(); // 할당

	device->Init();
	commandQueue->Init(device->GetDevice(), swapChain);
	swapChain->Init(hwnd, width, height, windowed, device->GetDevice(), device->GetDXGI(), commandQueue->GetCmdQueue());
	rootSignature->Init(device->GetDevice());
	constBuffer->Init(CBV_REGISTER::b0, sizeof(XMFLOAT4), 256);
	tableDesc->Init(256);

	input->Init(hwnd);

	//초기화
	timer->Init();

	ResizeWindow(_width, _height);
}


void GameEngine::Render()
{

	RenderBegin();
 
	RenderEnd();

}

void GameEngine::Update()
{
	input->Update();

	//timer 업데이트 실행
	timer->Update();

	//ShowFPS 호출
	ShowFPS();
}

void GameEngine::ShowFPS()
{
	//현재 FPS를 가져옴
	UINT32 fps = timer->GetFPS();

	//FPS값을 윈도 타이틀에 출력할 문자열 생성
	wstring fpsText = L"FPS: " + to_wstring(fps);

	//윈도 타이틀을 변경하여 FPS값을 표시 
	//SetWindowText(hwnd, fpsText.c_str());
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


	depthStencilBuffer->Init(width, height);
}
