#pragma once
#include "Object.h"

//�����Ͷ����� ������ �����ϴ� ������
enum class RASTERRIZER_TYPE
{
	CULL_NONE,	//�ø�����
	CULL_FRONT,	//�ո� �ø�
	CULL_BACK,	//�޸� �ø�
	WIREFRAME,	//���̾� ������ ���

};


//���� ���ٽ� �׽�Ʈ ������ ���� �ϴ� ������
enum class DEPTH_STENCIL_TYPE
{
	LESS,			//���� ���� ���� �� ���					<
	LESS_EQUAL, 	//���� ���� �۰ų� ���� �� ���			<=
	GREATER,		//���� ���� Ŭ�� ���					    >
	GREATER_EQUAL	//���� ���� ũ�ų� ���� �� ���			>=										 

};

//���̴� ������ ��� �ִ� ����ü
struct ShaderInfo
{
	//�⺻���� �޸� �ø��� ���
	RASTERRIZER_TYPE rasterrizerType = RASTERRIZER_TYPE::CULL_BACK;

	//�⺻������ ���� ���� ������ ���
	DEPTH_STENCIL_TYPE depthStencilType = DEPTH_STENCIL_TYPE::LESS;

};

class Shader : public Object
{
private:
	ComPtr<ID3DBlob> vsBlob; 
	ComPtr<ID3DBlob> psBlob; 
	ComPtr<ID3DBlob> errBlob;

	ComPtr<ID3D12PipelineState> pipelineState;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc = {};
public:
	Shader() : Object(OBJECT_TYPE::SHADER) {}
	virtual ~Shader() {}
private:
	void CreateShader(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shaderByteCode);
	void CreateVertexShader(const wstring& path, const string& name, const string& version);
	void CreatePixelShader(const wstring& path, const string& name, const string& version);
public:
	//�ʱ�ȭ
	void Init(const wstring& path, ShaderInfo info = ShaderInfo());
	void Update();
};

