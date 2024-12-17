#pragma once
class Shader
{
private:
	ComPtr<ID3DBlob> vsBlob; //���� ���̴� blob
	ComPtr<ID3DBlob> psBlob; //�ȼ� ���̴� blob
	ComPtr<ID3DBlob> errBlob;//���� blob

	ComPtr<ID3D12PipelineState> pipelineState; //���������� ���� ��ü
	//�׷��� ���������� ���� ������
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc = {};
private:
	//�־��� ��ο� �������� ���̴� ����
	void CreateShader(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shaderByteCode);
	//�־��� ��ο� �������� ���� ���̴� ����
	void CreateVertexShader(const wstring& path, const string& name, const string& version);
	//�־��� ��ο� �������� �ȼ� ���̴� ����
	void CreatePixelShader(const wstring& path, const string& name, const string& version);
public:
	//���̴��� �ʱ�ȭ(�־��� ����� ���̴� ������ ���)
	void Init(const wstring& path);
	//���̴� ���¸� ������Ʈ
	void Update();
};

