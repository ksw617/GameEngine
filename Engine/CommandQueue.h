#pragma once
class SwapChain;

class CommandQueue
{
private:
	//Direct3D 12 Ŀ�ǵ� ť
	ComPtr<ID3D12CommandQueue> cmdQueue;
	//Direct3D 12 Ŀ�ǵ� allocator
	ComPtr<ID3D12CommandAllocator> cmdAlloc;
	//Direct3D 12 �׷��� Ŀ�ǵ� ����Ʈ
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	//����ȭ ��ü�� �ҽ�
	ComPtr<ID3D12Fence> fence;

	//fence ��, CPU�� GPU���� ����ȭ�� ���� ���
	int fenceValue = 0;

	//fence �̺�Ʈ �ڵ�
	HANDLE fenceEvent = INVALID_HANDLE_VALUE;

	//SwapChain ��ü�� ���� ����Ʈ ������
	shared_ptr<SwapChain> swapChain;

public: //Get �Լ���
	//Ŀ�ǵ� ť ��ü�� ��ȯ�ϴ� �Լ�
	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return cmdQueue; }
	//�׷��� Ŀ�ǵ� ����Ʈ ��ü�� ��ȯ�ϴ� �Լ�
	ComPtr<ID3D12GraphicsCommandList> GetCmdList() { return cmdList; }

public:
	//�Ҹ���
	~CommandQueue();

	//CommandQueue �ʱ�ȭ �Լ�
	void Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain);

	//����ȭ�� ����ϴ� �Լ�
	void WaitSync();

	//������ ������ ���� ���� �Լ�
	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect);

	//������ ������ ����� �����ϴ� �Լ�
	void RenderEnd();

};

