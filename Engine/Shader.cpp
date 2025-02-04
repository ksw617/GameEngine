#include "pch.h"
#include "Shader.h"
#include "GameEngine.h"

void Shader::Init(const wstring& path, ShaderInfo info)
{
	CreateVertexShader(path, "VS_Main", "vs_5_0");
	CreatePixelShader(path, "PS_Main", "ps_5_0");

	D3D12_INPUT_ELEMENT_DESC desc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 20, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"TANGENT", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 32, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},

	
	};

	pipelineDesc.InputLayout = { desc, _countof(desc) };
	pipelineDesc.pRootSignature = GameEngine::Get().GetRootSignature()->GetSignature().Get();

	pipelineDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	pipelineDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	pipelineDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT); 
	pipelineDesc.SampleMask = UINT_MAX;
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	pipelineDesc.NumRenderTargets = 1;
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8_UNORM;
	pipelineDesc.SampleDesc.Count = 1;

	pipelineDesc.DSVFormat = GameEngine::Get().GetDepthStencilBuffer()->GetDSVFormat();

	switch (info.rasterrizerType)
	{
	case RASTERRIZER_TYPE::CULL_BACK:
		//�޸� �ø� ����ϰ�, �ָ��� ���� ����
		pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
		pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
		break;
	case RASTERRIZER_TYPE::CULL_FRONT:
		//�ո� �ø� ����ϰ�, �ָ��� ���� ����
		pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
		pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;
		break;
	case RASTERRIZER_TYPE::CULL_NONE:
		//�ø��� ������� �ʰ�, �ָ��� ���� ����
		pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
		pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
		break;
	case RASTERRIZER_TYPE::WIREFRAME:
		//�ø��� ������� �ʰ�, ���̾� ������ ���� ����
		pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
		pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
		break;
	}

	//���� ���ٽ� ������ ���� switch��
	switch (info.depthStencilType)		
	{
	case DEPTH_STENCIL_TYPE::LESS:
		//���� �׽�Ʈ�� Ȱ��ȭ�ϰ�, LESS �� �Լ��� ���
		pipelineDesc.DepthStencilState.DepthEnable = TRUE;
		pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
		break;
	case DEPTH_STENCIL_TYPE::LESS_EQUAL:
		//���� �׽�Ʈ�� Ȱ��ȭ�ϰ�, LESS_EQUAL �� �Լ��� ���
		pipelineDesc.DepthStencilState.DepthEnable = TRUE;
		pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
		break;
	case DEPTH_STENCIL_TYPE::GREATER:
		//���� �׽�Ʈ�� Ȱ��ȭ�ϰ�, GREATER �� �Լ��� ���
		pipelineDesc.DepthStencilState.DepthEnable = TRUE;
		pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_GREATER;
		break;
	case DEPTH_STENCIL_TYPE::GREATER_EQUAL:
		//���� �׽�Ʈ�� Ȱ��ȭ�ϰ�, GREATER_EQUAL �� �Լ��� ���
		pipelineDesc.DepthStencilState.DepthEnable = TRUE;
		pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_GREATER_EQUAL;
		break;
	}


	GameEngine::Get().GetDevice()->GetDevice()->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(&pipelineState));

}

void Shader::Update()
{
	GameEngine::Get().GetCmdQueue()->GetCmdList()->SetPipelineState(pipelineState.Get());
}


void Shader::CreateShader(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shaderByteCode)
{
	UINT32 compileFlag = 0;
#if  DEBIG
	compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	if (FAILED(D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, name.c_str(), version.c_str(), compileFlag, 0, &blob, &errBlob)))
	{
		MessageBoxA(nullptr, "Shader Craete Failed!", nullptr, MB_OK);
	}

	shaderByteCode = { blob->GetBufferPointer(), blob->GetBufferSize() };
}

void Shader::CreateVertexShader(const wstring& path, const string& name, const string& version)
{
	CreateShader(path, name, version, vsBlob, pipelineDesc.VS);
}

void Shader::CreatePixelShader(const wstring& path, const string& name, const string& version)
{	 
	CreateShader(path, name, version, psBlob, pipelineDesc.PS);
}

