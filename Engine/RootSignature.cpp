#include "pch.h"
#include "RootSignature.h"

void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	//samplerDesc ����� �Լ� ȣ��
	CreateSamplerDesc();

	CD3DX12_DESCRIPTOR_RANGE ranges[] =
	{
		CD3DX12_DESCRIPTOR_RANGE(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, CBV_REGISTER_COUNT, 0),
		//��ũ���� �������� ���߰� (SRV ������ Ÿ��, �������� ����, �⺻ ���̴� ��������)
		CD3DX12_DESCRIPTOR_RANGE(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, SRV_REGISTER_COUNT, 0)
	};

	CD3DX12_ROOT_PARAMETER params[1]{};


	params[0].InitAsDescriptorTable(_countof(ranges), ranges);

	//�Ű����� �߰�
	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(_countof(params), params, 1, &samplerDesc);
	
	sigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<ID3DBlob> blobSignature;
	ComPtr<ID3DBlob> blobError;

	D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);

	device->CreateRootSignature(0, blobSignature->GetBufferPointer(), blobSignature->GetBufferSize(), IID_PPV_ARGS(&signature));
}

void RootSignature::CreateSamplerDesc()
{
	//CD3DX12_STATIC_SAMPLER_DESC(0)�� �⺻ ���÷� �����ڸ� �����ϸ�,
	//�������� ���� 0�� ���̵���
	samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);
}
