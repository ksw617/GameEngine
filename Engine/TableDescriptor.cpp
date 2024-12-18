#include "pch.h"
#include "TableDescriptor.h"
#include "GameEngine.h" // ȣ��

void TableDescriptor::Init(UINT32 count)
{
	//�׷�� ����
	groupCount = count;

	//��ũ���� �� ��ũ��Ʈ ����
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = count * REGISTER_COUNT; // ��ü ��ũ��Ʈ ��
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // ���̴����� ���� ���̵��� ����
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; // ��Ÿ���� CBV/SRV/UAV�� ����

	//��ũ���� �� ����
	GameEngine::Get().GetDevice()->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&descHeap));
	
	//��ũ���� �ڵ� ũ�� ��������
	handleSize = GameEngine::Get().GetDevice()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//�׷� ũ�� ���(��ũ���� �ڵ� ũ�� * �������� ����)
	groupSize = handleSize * REGISTER_COUNT;
}

void TableDescriptor::Clear()
{
	//���� �׷� �ε����� 0���� �ʱ�ȭ �Ͽ� ��ũ���� ���� �ʱ� ���·� �缳��
	currentGroupIndex = 0;
}

void TableDescriptor::SetCBV(D3D12_CPU_DESCRIPTOR_HANDLE srcHandle, CBV_REGISTER reg)
{
	//�־��� �������Ϳ� ���� CPU ��ũ���� �ڵ��� ������
	D3D12_CPU_DESCRIPTOR_HANDLE descHandle = GetCPUHandle(reg);

	UINT32 descRange = 1;	//��� ������ 1���� ��ũ����
	UINT32 srcRange = 1;	//�ҽ� ������ 1���� ��ũ����

	GameEngine::Get().GetDevice()->GetDevice()->CopyDescriptors
	(
		1, &descHandle, &descRange, // ��� ��ũ����
		1, &srcHandle, &srcRange,	// �ҽ� ��ũ����
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV // ��ũ���� �� Ÿ��
	);
}

D3D12_CPU_DESCRIPTOR_HANDLE TableDescriptor::GetCPUHandle(CBV_REGISTER reg)
{
	//CBV_REGISTER �������� UIN32�� ��ȯ�Ͽ� �����ε�� GetCPUHandle�� ȣ��
	return GetCPUHandle(static_cast<UINT32>(reg));
}

D3D12_CPU_DESCRIPTOR_HANDLE TableDescriptor::GetCPUHandle(UINT32 reg)
{
	//��ũ���� ���� ���� CPU ��ũ���� �ڵ� ������
	D3D12_CPU_DESCRIPTOR_HANDLE handle = descHeap->GetCPUDescriptorHandleForHeapStart();

	//���� �׷� �ε����� �������� �ڵ��� ������
	handle.ptr += currentGroupIndex * groupSize;
	handle.ptr += reg * handleSize;

	return handle;
}
