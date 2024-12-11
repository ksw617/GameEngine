#include "pch.h"
#include "CommandQueue.h"
#include "SwapChain.h" // ȣ��

CommandQueue::~CommandQueue()
{
	//�ҽ� �̺�Ʈ �ڵ��� �ݾƼ� ���ҽ��� ����
	CloseHandle(fenceEvent);
}

void CommandQueue::Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain)
{
	//SwapChain�� ����
	this->swapChain = swapChain;

	//Ŀ�ǵ� ť description ����ü �ʱ�ȭ
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT; // Ŀ�ǵ� ����Ʈ Ÿ�� ����
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE; // �÷��� ����

	//Ŀ�ǵ� ť ����
	device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&cmdQueue));

	//Ŀ�ǵ� allocator ����
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&cmdAlloc));

	//Ŀ�ǵ� ����Ʈ ����
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, cmdAlloc.Get(), nullptr, IID_PPV_ARGS(&cmdList));

	//Ŀ�ǵ� ����Ʈ�� ����. �缳���� ����
	cmdList->Close();

	//�ҽ� ��ü ����
	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));

	//�ҽ� �̺�Ʈ ����
	fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

//CPU�� GPU���� ����ȭ�� ����ϴ� �Լ�
void CommandQueue::WaitSync()
{
	//�ҽ� �� ����
	fenceValue++;

	//GPU�� �ҽ� ��ȣ ������
	cmdQueue->Signal(fence.Get(), fenceValue);
											   
	//�ҽ� ���� �Ϸ�� ������ �̺�Ʈ ���
	if (fence->GetCompletedValue() < fenceValue)
	{
		//�ҽ� ���� �Ϸ�Ǿ��� �� �̺�Ʈ ����
		fence->SetEventOnCompletion(fenceValue, fenceEvent);

		//�̺�Ʈ ���
		WaitForSingleObject(fenceEvent, INFINITE);
	}
}

//������ �����ϱ� ���� ���� �Լ�
void CommandQueue::RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect)
{
	//Ŀ�ǵ� alloc�� �缳��
	cmdAlloc->Reset();

	//Ŀ�ǵ� ����Ʈ �缳��
	cmdList->Reset(cmdAlloc.Get(), nullptr);

	//���ҽ� ����� �����Ͽ� ���� ���¸� Present���� Render Target���� ��ȯ
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_PRESENT,	  //from
		D3D12_RESOURCE_STATE_RENDER_TARGET);//to

	//���ҽ� ������ ����
	cmdList->ResourceBarrier(1, &barrier);

	//����Ʈ ����
	cmdList->RSSetViewports(1, vp);

	//����(Rect) ����
	cmdList->RSSetScissorRects(1, rect);

	//�� ������ ���� Ÿ�� �並 ������
	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = swapChain->GetBackRTV();

	//���� Ÿ�� �並 Ŭ����
	cmdList->ClearRenderTargetView(backBufferView, Colors::Aqua, 0, nullptr);

	//���� Ÿ�� ����
	cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, nullptr);

}

void CommandQueue::RenderEnd()
{

	//���ҽ� ����� �����Ͽ� ���� ���¸� Render Target���� Present���� ��ȯ
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,	//from
		D3D12_RESOURCE_STATE_PRESENT); //to

	//���ҽ� ������ ����
	cmdList->ResourceBarrier(1, &barrier);

	//Ŀ�ǵ� ����Ʈ�� ����
	cmdList->Close();

	//Ŀ�ǵ� ����Ʈ�� Ŀ�ǵ� ����Ʈ �迭 ���� 
	ID3D12CommandList* cmdListArr[] = { cmdList.Get() };

	//Ŀ�ǵ� ����Ʈ�� ����
	cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	//���� ü���� ���� ȭ�鿡 ���
	swapChain->Present();

	//����ȭ ���
	WaitSync();

	//�� ���� �ε��� ��ȯ
	swapChain->SwapIndex();
	
}
