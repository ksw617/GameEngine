#include "pch.h"
#include "Device.h"

void Device::Init()
{
	//����� ��尡 Ȱ��ȭ �Ǿ� ���� ���
#if _DEBUG
	//����� �������̽��� ��û�Ͽ� debugControoler�� ����
	D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
	//����� ���̾ Ȱ��ȭ�Ͽ� ���� �� ������ ���� ã�� �� �ְ� ��
	debugController->EnableDebugLayer();
#endif

	//DXGI ���丮 �����ؼ� dxgiFactory�� ����
	//DXGI ���丮�� �پ��� DXGI ��ü�� �����ϴµ� ���
	CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));

	//DirectX 12 ����̽� ����, &device�� ����
	//�� ����̽��� Direct3D ����� ����Ͽ� �׷��� ���ҽ��� �����ϰ� �����ϴµ� �ʼ� ���
	//nullptr : �⺻ ��� ��� �ϰڴٴ� �ǹ�
    //D3D_FEATURE_LEVEL_11_0 : �ּ� �����ؾ� �� ��� ����
	D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));

}
