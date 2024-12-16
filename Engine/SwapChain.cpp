#include "pch.h"
#include "SwapChain.h"

//SwapChain 초기화
void SwapChain::Init(HWND hwnd, int width, int height, bool windowed, ComPtr<ID3D12Device> device, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue)
{
	//스왑 체인 생성
	CreateSwapChain(hwnd, width, height, windowed, dxgi, cmdQueue);
	//렌더 타겟 뷰(RTV) 생성
	CreatRTV(device);
}

//현재 백 버퍼의 내용을 화면에 출력하는 함수
void SwapChain::Present()
{
	//Vsync를 사용 하지 않고 화면 출력
	swapChain->Present(0,0);
}

void SwapChain::SwapIndex()
{
	//백 버퍼 인덱스를 순환하여 해당 버퍼 인덱스를 교환
	backBufferIndex = (backBufferIndex + 1) % 2;
}


void SwapChain::CreateSwapChain(HWND hwnd, int width, int height, bool windowed, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue)
{
	swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC sd;

	sd.BufferDesc.Width = static_cast<unsigned int>(width);
	sd.BufferDesc.Height = static_cast<unsigned int>(height);

	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;

	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	sd.BufferCount = 2;

	sd.OutputWindow = hwnd;


	sd.Windowed = windowed;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // 수정
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


	//스왑체인 생성
	dxgi->CreateSwapChain(cmdQueue.Get(), &sd, &swapChain);


	for (int i = 0; i < 2; i++)
	{
		swapChain->GetBuffer(i, IID_PPV_ARGS(&rtvBuffer[i]));
	}

}


void SwapChain::CreatRTV(ComPtr<ID3D12Device> device)
{

	int rtvHeapSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	D3D12_DESCRIPTOR_HEAP_DESC rtvDesc;

	rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvDesc.NumDescriptors = 2;
	rtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvDesc.NodeMask = 0;

	device->CreateDescriptorHeap(&rtvDesc, IID_PPV_ARGS(&rtvHeap));

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapBegin = rtvHeap->GetCPUDescriptorHandleForHeapStart();

	for (int i = 0; i < 2; i++)
	{
													// + -> *	
		rtvHandle[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeapBegin, i * rtvHeapSize);

		device->CreateRenderTargetView(rtvBuffer[i].Get(), nullptr, rtvHandle[i]);
	}

}
