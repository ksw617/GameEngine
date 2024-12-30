#include "pch.h"
#include "DepthStencilBuffer.h"
#include "GameEngine.h"

void DepthStencilBuffer::Init(int width, int height, DXGI_FORMAT _desvFormat)
{
	//���� ���ٽ� ���� ���� ����
	dsvFormat = _desvFormat;

	//�� �Ӽ� ����(����Ʈ �� Ÿ��)
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	
	//���ҽ� ������ ����(�ؽ�ó 2D(���� ���ٽ� ����, �ʺ�, ����))
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Tex2D(dsvFormat, width, height);
	desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL; // ���� ���ٽ� �÷��� ����

	//����ȭ�� Ŭ���� �� ����(���� 1.0, ���ٽ� 0)
	D3D12_CLEAR_VALUE optimizedClearValue = CD3DX12_CLEAR_VALUE(dsvFormat, 1.0f, 0);

	//���� ���ٽ� ���� ���ҽ� ����
	GameEngine::Get().GetDevice()->GetDevice()->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&optimizedClearValue,
		IID_PPV_ARGS(&dsvBuffer));

	//��ũ���� �� ������ ����(���� / ���ٽ� ��)
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.NumDescriptors = 1; // ��ũ���� �� 1��
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE; // �÷��� ����
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; // ���� ���ٽ� �� Ÿ��

	//��ũ���� �� ����
	GameEngine::Get().GetDevice()->GetDevice()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&dsvHeap));

	//���� ���ٽ� ���� cpu ��ũ���� �ڵ� ��������
	dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();

	//���� ���ٽ� �� ����
	GameEngine::Get().GetDevice()->GetDevice()->CreateDepthStencilView(dsvBuffer.Get(), nullptr, dsvHandle);

}
