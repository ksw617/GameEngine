#pragma once
class DepthStencilBuffer
{
private:
	//���� ���ٽ� ���� ���ҽ�
	ComPtr<ID3D12Resource> dsvBuffer;
	//���� ���ٽ� �� ��ũ���� ��
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	//���� ���ٽ� ���� CPU ��ũ���� �ڵ�
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = {};
	//���� ���ٽ� ���� ����
	DXGI_FORMAT dsvFormat = {};

public:
	//���� ���ٽ� ���� CPU ��ũ���� �ڵ��� ��ȯ �ϴ� �Լ�
	D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCPUHandle() { return dsvHandle; }

	//���� ���ٽ� ���� ������ ��ȯ�ϴ� �Լ�
	DXGI_FORMAT GetDSVFormat() { return dsvFormat; }
public:
	//���� ���ٽ� ������ �ʱ�ȭ
	void Init(int width, int height, DXGI_FORMAT _desvFormat = DXGI_FORMAT_D32_FLOAT);
};

