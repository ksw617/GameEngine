#pragma once
class TableDescriptor
{
private:
	ComPtr<ID3D12DescriptorHeap> descHeap;	// ��ũ���� ��
	UINT64 handleSize = 0;					// ��ũ���� �ڵ� ũ��
	UINT64 groupSize = 0;					// �׷�� ��ũ���� ��
	UINT64 groupCount = 0;					// �׷��� ��

	UINT32 currentGroupIndex = 0;			// ���� �׷� �ε���
public:
	//descHeap Get �Լ�
	ComPtr<ID3D12DescriptorHeap> GetDescriptorHeap() { return descHeap; }
public:
	//��ũ��Ʈ �� �ʱ�ȭ
	void Init(UINT32 count);

	//index �ʱ�ȭ
	void Clear();

	//��� ���� ��(CBV) ����
	void SetCBV(D3D12_CPU_DESCRIPTOR_HANDLE srcHandle, CBV_REGISTER reg);

	//�־��� �������Ϳ� ���� CPU ��ũ���� �ڵ� ��������
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(CBV_REGISTER reg);

private:
	//�־��� �ε����� ���� CPU ��ũ���� �ڵ� ��������
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(UINT32 reg);


};

