#pragma once
class SwapChain
{
private:
	//SwapChain	��ü
	ComPtr<IDXGISwapChain> swapChain;

	//RTV(Render Taget View)
	//���� Ÿ�� ���� �迭(���� ���۸��� �ϱ� ���� 2�� ���)
	ComPtr<ID3D12Resource> rtvBuffer[2];
	//RTV�� ���� ��ũ���� ��
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	//Render target view ��ũ���� �ڵ� �迭
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle[2];

	//���� ��� ���� �� ������ �ε���
	int backBufferIndex = 0;

public: // Get �Լ��� ����
	//SwapChain ��ü�� ��ȯ
	ComPtr<IDXGISwapChain> GetSwapChain() { return swapChain; }
	//�־��� �ε����� �ش��ϴ� ���� Ÿ�� ���� ��ȯ
	ComPtr<ID3D12Resource> GetRednerTarget(int index) { return rtvBuffer[index]; }
	//���� �� ���ۿ� �ش��ϴ� ���� Ÿ�� ���۸� ��ȯ
	ComPtr<ID3D12Resource> GetBackRTVBuffer() const { return rtvBuffer[backBufferIndex]; }
	//���� �� ������ ���� Ÿ�� ��(RTV) ��ũ���� �ڵ��� ��ȯ
	D3D12_CPU_DESCRIPTOR_HANDLE GetBackRTV() const { return rtvHandle[backBufferIndex]; }

public:
	//�ʱ�ȭ �Լ�, �ʿ��� ������ ��ü�� �޾� ����ü�ΰ� ���� ���ҽ��� ����
	void Init(HWND hwnd, int width, int height, bool windowed, ComPtr<ID3D12Device> device, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);

	//ȭ�鿡 �������� ������ ǥ��, �� ���ۿ� ����Ʈ ���۸� ��ȯ
	void Present();
	//�� ���� �ε����� ����, �������� ���� ���۸� ����
	void SwapIndex();
private:
	//����ü���� �����ϴ� ���� �Լ�
	void CreateSwapChain(HWND hwnd, int width, int height, bool windowed, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);
	//���� Ÿ�� ��(RTV)�� �����ϴ� ���� �Լ�
	void CreatRTV(ComPtr<ID3D12Device> device);
};

