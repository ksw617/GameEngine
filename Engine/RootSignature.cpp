#include "pch.h"
#include "RootSignature.h"

//��Ʈ �ñ״�ó �ʱ�ȭ
void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	//�ΰ��� ��Ʈ �Ķ���� �迭 ����
	CD3DX12_ROOT_PARAMETER params[2];

	//ù��° ��Ʈ �Ķ���͸� ��� ���� ��� �ʱ�ȭ, �������� b0�� ���ε�
	params[0].InitAsConstantBufferView(0); //0�� -> b0

	//�ι�° ��Ʈ �Ķ���͸� ��� ���� ��� �ʱ�ȭ, �������� b1�� ���ε�
	params[1].InitAsConstantBufferView(1); //1�� -> b1

	//��Ʈ �ñ״�ó ������ ����, �ΰ��� ��Ʈ �Ķ���� ���
	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(2, params);
	sigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<ID3DBlob> blobSignature;

	ComPtr<ID3DBlob> blobError;

	D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);

	device->CreateRootSignature(0, blobSignature->GetBufferPointer(), blobSignature->GetBufferSize(), IID_PPV_ARGS(&signature));
}
