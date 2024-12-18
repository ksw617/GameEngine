#include "pch.h"
#include "RootSignature.h"

//��Ʈ �ñ״�ó �ʱ�ȭ
void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	//��� ���� ��(CBV) ������ �迭 ����
	CD3DX12_DESCRIPTOR_RANGE ranges[] =
	{
		//CBV ������ Ÿ��, �������� ����, �⺻ ���̴� ��������
		CD3DX12_DESCRIPTOR_RANGE(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, CBV_REGISTER_COUNT, 0)
	};

	//��Ʈ �Ķ���� �迭 ����
	CD3DX12_ROOT_PARAMETER params[1]{};

	//params[0].InitAsConstantBufferView(0);
	//params[1].InitAsConstantBufferView(1);

	//�Ķ���� ��ũ���� ���̺�� �ʱ�ȭ
	//(_countof(ranges) : �迭�� ����
	params[0].InitAsDescriptorTable(_countof(ranges), ranges);

	//��Ʈ �ñ״�ó ������ ����. ���� �Ķ���� ���
	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(_countof(ranges), params);
	
	sigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<ID3DBlob> blobSignature;
	ComPtr<ID3DBlob> blobError;

	D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);

	device->CreateRootSignature(0, blobSignature->GetBufferPointer(), blobSignature->GetBufferSize(), IID_PPV_ARGS(&signature));
}
