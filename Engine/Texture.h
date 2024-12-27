#pragma once
class Texture
{
private:
	ScratchImage image; // �̹��� �����͸� �����ϴ� ScratchImage ��ü
	ComPtr<ID3D12Resource> texture2D; // �ؽ�ó ���ҽ�

	ComPtr<ID3D12DescriptorHeap> srvHeap;	//���̴� ���ҽ� ��(SRV) ��ũ���� ��
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;	//SRV�� CPU ��ũ���� �ڵ�

public:
	//SRV�� CPU ��ũ���� �ڵ��� Get �ϴ� �Լ�
	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle() { return srvHandle; }
public:
	//�ؽ�ó�� �ʱ�ȭ�ϴ� �Լ�(���� ��θ� ���ڸ� �־���)
	void Init(const wstring& path);
private:
	//���� ��θ� �޾� �ؽ�ó�� �����ϴ� �Լ�
	void CreateTexture(const wstring& path);
	//�ؽ�ó�� ���� ��(SRV)�� �����ϴ� �Լ�
	void CreateView();
};

