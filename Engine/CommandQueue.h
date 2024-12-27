#pragma once
class SwapChain;

class CommandQueue
{
private:
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<ID3D12CommandAllocator> cmdAlloc;
	ComPtr<ID3D12GraphicsCommandList> cmdList;

	ComPtr<ID3D12CommandAllocator> resCmdAlloc; // ���ҽ� ��� �Ҵ���
	ComPtr<ID3D12GraphicsCommandList> resCmdList;// ���ҽ� ��� ����Ʈ

	ComPtr<ID3D12Fence> fence;
	int fenceValue = 0;
	HANDLE fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain> swapChain;

public:
	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList> GetCmdList() { return cmdList; }
	//���ҽ� ��� ����Ʈ�� Get�ϴ� �Լ�
	ComPtr<ID3D12GraphicsCommandList> GetResourceCmdList() { return resCmdList; }

public:
	~CommandQueue();
	void Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain);
	void WaitSync();
	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect);
	void RenderEnd();

	//���ҽ� ��� ��⿭�� submit�Ѵ� �Լ�
	void SubmitResourceCommandQueue();

};

