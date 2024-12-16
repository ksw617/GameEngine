#include "pch.h"
#include "RootSignature.h"

//��Ʈ �ñ״�ó �ʱ�ȭ
void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	//�⺻ ������ ����Ͽ� ��Ʈ �ñ״�ó�� �����ϰ� �Է� ������ �ܰ踦 ���
	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(D3D12_DEFAULT);
	sigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	//����ȭ�� ��Ʈ �ñ״�ó�� �����ϴ� blob
	ComPtr<ID3DBlob> blobSignature;

	//����ȭ ���� �� ���� �޼��� �����ϴ� blob
	ComPtr<ID3DBlob> blobError;

	//��Ʈ �ñ״�ó�� ����ȭ
	D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);

	//����ȭ�� �����͸� ����Ͽ� ��Ʈ �ñ״�ó ����
	device->CreateRootSignature(0, blobSignature->GetBufferPointer(), blobSignature->GetBufferSize(), IID_PPV_ARGS(&signature));
}
