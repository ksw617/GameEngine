#pragma once
class ConstantBuffer
{
private:
	//��� ���� ���ҽ�
	ComPtr<ID3D12Resource> cbvBuffer;
	//���ε� ���� ������ ������
	BYTE* mappedBuffer = nullptr;
	//�� ����� ũ��
	int elementSize = 0;
	//����� ����
	int elementCount = 0;
	//���� �ε���
	int currentIndex = 0;
public:
	ConstantBuffer();
	~ConstantBuffer();
private:
	//��� ���� ����
	void CreateBuffer();
public:
	//��� ���� �ʱ�ȭ
	void Init(int size, int count);
	//��� ���� ������ �ʱ�ȭ
	void Clear();
	//��� ���ۿ� ������ Ǫ��
	void PushData(int rootParamIndex, void* buffer, int size);

	//GPU ���� �ּ� ��������
	D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress(int index);
};

