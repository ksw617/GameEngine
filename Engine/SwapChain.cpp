#include "pch.h"
#include "SwapChain.h"

//SwapChain �ʱ�ȭ
void SwapChain::Init(HWND hwnd, int width, int height, bool windowed, ComPtr<ID3D12Device> device, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue)
{
	//���� ü�� ����
	CreateSwapChain(hwnd, width, height, windowed, dxgi, cmdQueue);
	//���� Ÿ�� ��(RTV) ����
	CreatRTV(device);
}

//���� �� ������ ������ ȭ�鿡 ����ϴ� �Լ�
void SwapChain::Present()
{
	//Vsync�� ��� ���� �ʰ� ȭ�� ���
	swapChain->Present(0,0);
}

void SwapChain::SwapIndex()
{
	//�� ���� �ε����� ��ȯ�Ͽ� �ش� ���� �ε����� ��ȯ
	backBufferIndex = (backBufferIndex + 1) % 2;
}


void SwapChain::CreateSwapChain(HWND hwnd, int width, int height, bool windowed, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue)
{
	//���� SwapChain ����
	swapChain.Reset();

	//���� ü�� ���� ����ü �ʱ�ȭ
	DXGI_SWAP_CHAIN_DESC sd;

	//���� �� ����
	sd.BufferDesc.Width = static_cast<unsigned int>(width);
	//������ ���� ����
	sd.BufferDesc.Height = static_cast<unsigned int>(height);

	//ȭ�� �����(����)
	sd.BufferDesc.RefreshRate.Numerator = 60;
	//ȭ�� �����(�и�)
	sd.BufferDesc.RefreshRate.Denominator = 1;


	//���� ���� ����
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//��ĵ���� ����
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	 //������ ��� ����
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//��Ƽ ���ø� �� ����(1�̸� ��Ȱ��ȭ)
	sd.SampleDesc.Count = 1;
	//��Ƽ ���ø� ����
	sd.SampleDesc.Quality = 0;

	//���� ��� ��� ����
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//���� �� ����(���� ����)
	sd.BufferCount = 2;

	//��� â �ڵ� ����
	sd.OutputWindow = hwnd;

	//â��� ����
	sd.Windowed = windowed;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // ���� ȿ�� ����
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // ��� ��ȯ ��� ����


	//����ü�� ����
	dxgi->CreateSwapChain(cmdQueue.Get(), &sd, &swapChain);

	//�� ���۸� tryBuffer �迭�� ����
	for (int i = 0; i < 2; i++)
	{
		swapChain->GetBuffer(i, IID_PPV_ARGS(&rtvBuffer[i]));
	}

}

//���� Ÿ�� ��(RTV)�� ���� �ϴ� �Լ�
void SwapChain::CreatRTV(ComPtr<ID3D12Device> device)
{
	//RTV ��ũ���� ���� ũ�� ���
	int rtvHeapSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	//RTV ��ũ���� ����ü �ʱ�ȭ
	D3D12_DESCRIPTOR_HEAP_DESC rtvDesc;

	//��ũ���� �� Ÿ�� ����
	rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

	//��ũ���� �� ����(���� ���۸�)
	rtvDesc.NumDescriptors = 2;
	//��ũ���� �� �÷��� ����
	rtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	//��� ����ũ ����(���� ����� ��� 0)
	rtvDesc.NodeMask = 0;

	//RTV ��ũ���� �� ����
	device->CreateDescriptorHeap(&rtvDesc, IID_PPV_ARGS(&rtvHeap));

	//RTV ��ũ���� ���� ���� �ڵ� ��������
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapBegin = rtvHeap->GetCPUDescriptorHandleForHeapStart();

	//�� ���ۿ� ���� RTV ����
	for (int i = 0; i < 2; i++)
	{
		//RTV �ڵ� ����
		rtvHandle[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeapBegin, i + rtvHeapSize);

		//RTV ����
		device->CreateRenderTargetView(rtvBuffer[i].Get(), nullptr, rtvHandle[i]);
	}

}
