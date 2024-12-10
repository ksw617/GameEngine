#pragma once
class Device
{
private:
	//����� ��Ʈ�ѷ�, DirectX 12 ����� ����� ����
	ComPtr<ID3D12Debug> debugController;
	//DXGI ���丮, ȭ�� ��� �� �׷��� ī�� ������� ����
	ComPtr<IDXGIFactory> dxgiFactory;
	//D3D12 ����̽�, �׷��� ���ҽ� ������ ���
	ComPtr<ID3D12Device> device;

public:
	//DXGI ���丮 ��ü�� �˻�(����� DXGI ��ü ������ ���)
	ComPtr<IDXGIFactory> GetDXGI() { return  dxgiFactory; }

	//D3D12 ����̽� ��ü�� �˻�(�׷��� ���ҽ� ������ ���) 
	ComPtr<ID3D12Device> GetDevice() { return device; }

public:
	//��ġ �� ���� ���� ��� �ʱ�ȭ
	void Init();
};

