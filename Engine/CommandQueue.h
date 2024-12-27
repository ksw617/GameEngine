#pragma once
class SwapChain;

class CommandQueue
{
private:
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<ID3D12CommandAllocator> cmdAlloc;
	ComPtr<ID3D12GraphicsCommandList> cmdList;

	ComPtr<ID3D12CommandAllocator> resCmdAlloc; // 리소스 명령 할당자
	ComPtr<ID3D12GraphicsCommandList> resCmdList;// 리소스 명령 리스트

	ComPtr<ID3D12Fence> fence;
	int fenceValue = 0;
	HANDLE fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain> swapChain;

public:
	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList> GetCmdList() { return cmdList; }
	//리소스 명령 리스트는 Get하는 함수
	ComPtr<ID3D12GraphicsCommandList> GetResourceCmdList() { return resCmdList; }

public:
	~CommandQueue();
	void Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain);
	void WaitSync();
	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect);
	void RenderEnd();

	//리소스 명령 대기열을 submit한는 함수
	void SubmitResourceCommandQueue();

};

