#include "pch.h"
#include "CommandQueue.h"
#include "SwapChain.h" 
#include "GameEngine.h" 

CommandQueue::~CommandQueue()
{
	CloseHandle(fenceEvent);
}

void CommandQueue::Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain)
{
	this->swapChain = swapChain;

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT; 
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE; 

	device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&cmdQueue));
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAlloc));
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAlloc.Get(), nullptr, IID_PPV_ARGS(&cmdList));

	cmdList->Close();

	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void CommandQueue::WaitSync()
{
	fenceValue++;

	cmdQueue->Signal(fence.Get(), fenceValue);
											   
	if (fence->GetCompletedValue() < fenceValue)
	{
		fence->SetEventOnCompletion(fenceValue, fenceEvent);
		WaitForSingleObject(fenceEvent, INFINITE);
	}
}

void CommandQueue::RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect)
{
	cmdAlloc->Reset();
	cmdList->Reset(cmdAlloc.Get(), nullptr);

	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_PRESENT,	 
		D3D12_RESOURCE_STATE_RENDER_TARGET);

	cmdList->SetGraphicsRootSignature(GameEngine::Get().GetRootSignature()->GetSignature().Get());
	GameEngine::Get().GetConstBuffer()->Clear();
	GameEngine::Get().GetTableDesc()->Clear();

	ID3D12DescriptorHeap* descHeap = GameEngine::Get().GetTableDesc()->GetDescriptorHeap().Get();
	cmdList->SetDescriptorHeaps(1, &descHeap);
	cmdList->ResourceBarrier(1, &barrier);
	cmdList->RSSetViewports(1, vp);
	cmdList->RSSetScissorRects(1, rect);

	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = swapChain->GetBackRTV();

	cmdList->ClearRenderTargetView(backBufferView, Colors::Black, 0, nullptr);
	//ÁÖ¼®
	//cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, nullptr);

	//±íÀÌ ½ºÅÙ½Ç ºäÀÇ CPU µð½ºÅ©¸³ÅÍ ÇÚµéÀ» °¡Á®¿È
	D3D12_CPU_DESCRIPTOR_HANDLE depthStencilView = GameEngine::Get().GetDepthStencilBuffer()->GetDSVCPUHandle();
	//±âÁ¸²¬ ¾ê·Î º¯°æ 
	//Ãâ·Â º´ÇÕ ´Ü°è¿¡ ·£´õ Å¸°Ù°ú ±íÀÌ ½ºÅÙ½Ç ºä¸¦ ¼³Á¤
	cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, &depthStencilView);
	
	//±íÀÌ ½ºÅÙ½Ç ºä¸¦ ÃÊ±âÈ­
	//±íÀÌ °ªÀ» 1.0À¸·Î ÃÊ±âÈ­ ÇÏ°í ½ºÅÙ½Ç °ªÀº 0À¸·Î ÃÊ±âÈ­
	cmdList->ClearDepthStencilView(depthStencilView, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

}

void CommandQueue::RenderEnd()
{

	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,	
		D3D12_RESOURCE_STATE_PRESENT); 

	cmdList->ResourceBarrier(1, &barrier);
	cmdList->Close();

	ID3D12CommandList* cmdListArr[] = { cmdList.Get() };

	cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	swapChain->Present();

	WaitSync();

	swapChain->SwapIndex();
	
}

void CommandQueue::SubmitResourceCommandQueue()
{
	resCmdList->Close();

	ID3D12CommandList* cmdListArr[] = { resCmdList.Get() };

	cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	WaitSync();

	resCmdAlloc->Reset();

	resCmdList->Reset(resCmdAlloc.Get(), nullptr);
}
