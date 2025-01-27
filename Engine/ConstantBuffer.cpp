#include "pch.h"
#include "ConstantBuffer.h"
#include "GameEngine.h"

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
	if (cbvBuffer)
	{
		if (cbvBuffer != nullptr)
		{
			cbvBuffer->Unmap(0, nullptr);

			cbvBuffer = nullptr;
		}

	}
}

void ConstantBuffer::Init(CBV_REGISTER reg, UINT32 size, UINT32 count)
{	   	
	cbvRegister = reg;

	elementSize = (size + 255) & ~255; 
	elementCount = count;

	CreateBuffer();
	CreateView();
}

void ConstantBuffer::CreateBuffer()
{
	int bufferSize = elementSize * elementCount;
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	GameEngine::Get().GetDevice()->GetDevice()->CreateCommittedResource
	(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&cbvBuffer)
	);

	cbvBuffer->Map(0, nullptr, reinterpret_cast<void**>(&mappedBuffer));
}

void ConstantBuffer::CreateView()
{

	D3D12_DESCRIPTOR_HEAP_DESC cbvDesc = {};
	cbvDesc.NumDescriptors = elementCount; 
	cbvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	cbvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	GameEngine::Get().GetDevice()->GetDevice()->CreateDescriptorHeap(&cbvDesc, IID_PPV_ARGS(&cbvDescHeap));

	cpuHandleBegin = cbvDescHeap->GetCPUDescriptorHandleForHeapStart();
	handleIncrementSize = GameEngine::Get().GetDevice()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	for (UINT32 i = 0; i < elementCount; i++)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE cbvHandle = GetCPUHandle(i);
		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc = {};

		cbvDesc.BufferLocation = cbvBuffer->GetGPUVirtualAddress() + static_cast<UINT64>(elementSize) * i;
		cbvDesc.SizeInBytes = elementSize;

		GameEngine::Get().GetDevice()->GetDevice()->CreateConstantBufferView(&cbvDesc, cbvHandle);


	}
}
	

void ConstantBuffer::Clear()
{
	currentIndex = 0;
}

void ConstantBuffer::PushData(void* buffer, UINT32 size)
{
	assert(currentIndex < elementCount);
	assert(elementSize == ((size + 255) & ~255));

	memcpy(&mappedBuffer[currentIndex * elementSize], buffer, size);

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = GetCPUHandle(currentIndex);
	GameEngine::Get().GetTableDesc()->SetCBV(cpuHandle, cbvRegister);

	currentIndex++;
}

void ConstantBuffer::PushGlobalData(void* buffer, UINT32 size)
{
	//��� ũ�Ⱑ 256����Ʈ ������ ������ �ִ��� Ȯ��
	assert(elementSize == ((size + 255) & ~255));

	//���ε� ������ ���� �κп� ������ ����
	memcpy(&mappedBuffer[0], buffer, size);

	//�׷��� ��� ����Ʈ�� ��Ʈ ���� ��� ���� �並 ����
	//��Ʈ �Ķ���� �ε��� 0���� ��� ������ GPU ���� �ּҸ� ����
	GameEngine::Get().GetCmdQueue()->GetCmdList()->SetGraphicsRootConstantBufferView(0, GetGPUVirtualAddress(0));
}

D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetGPUVirtualAddress(UINT32 index)
{
	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = cbvBuffer->GetGPUVirtualAddress();
	objCBAddress += index * elementSize; 

	return objCBAddress;
}

D3D12_CPU_DESCRIPTOR_HANDLE ConstantBuffer::GetCPUHandle(UINT32 index)
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(cpuHandleBegin, index * handleIncrementSize);
}




