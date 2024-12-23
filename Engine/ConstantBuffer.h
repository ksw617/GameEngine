#pragma once
class ConstantBuffer
{
private:
	ComPtr<ID3D12Resource> cbvBuffer;
	BYTE* mappedBuffer = nullptr;

	UINT32 elementSize = 0;
	UINT32 elementCount = 0;
	UINT32 currentIndex = 0;
private:
	//CBV ��ũ���� ��
	ComPtr<ID3D12DescriptorHeap> cbvDescHeap;
	//��ũ���� ���� ���� CPU �ڵ�
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandleBegin = {};
	//��ũ���� �ڵ��� ���� ũ��
	UINT32 handleIncrementSize = 0;
	//��� ���� ��(CBV) ��������
	CBV_REGISTER cbvRegister = {};

public:
	ConstantBuffer();
	~ConstantBuffer();
private:
	void CreateBuffer();
	//View �����
	void CreateView();
public:
	//��� ���� �ʱ�ȭ
	void Init(CBV_REGISTER reg, UINT32 size, UINT32 count);
	void Clear();
	//��� ���ۿ� ������ Ǫ��
	void PushData(void* buffer, UINT32 size);

	D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress(UINT32 index);

	//CPU ��ũ���� �ڵ� Get �Լ�
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(UINT32 index);
};

