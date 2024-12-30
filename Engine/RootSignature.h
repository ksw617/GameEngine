#pragma once
class RootSignature
{
private:
	ComPtr<ID3D12RootSignature> signature;
	//���÷� ������
	D3D12_STATIC_SAMPLER_DESC samplerDesc;
public:
	ComPtr<ID3D12RootSignature> GetSignature() const { return signature; }
public:
	void Init(ComPtr<ID3D12Device> device);

	//���÷� �����ڸ� �����ϴ� �Լ�
	void CreateSamplerDesc();
};

