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
};

