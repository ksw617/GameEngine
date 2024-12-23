#pragma once
class Mesh
{
private:
	ComPtr<ID3D12Resource> vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView = {};
	UINT32 vertexCount = 0;
	
	ComPtr<ID3D12Resource> indexBuffer;		// �ε��� ���� ���ҽ�
	D3D12_INDEX_BUFFER_VIEW indexBufferView;// �ε��� ���� ��
	UINT32 indexCount = 0;					// �ε��� ����

	XMFLOAT4 transform = {};
public:
	//���� ���ۿ� �ε��� ���۸� �ʱ�ȭ
	void Init(const vector<Vertex>& vertexBuffer, const vector<UINT32>& indexBuffer);
	void Render();

	void SetTransform(const XMFLOAT4& _transform) { transform = _transform; }

private:
	//���� ���� ����
	void CreateVertexBuffer(const vector<Vertex>& buffer);
	//�ε��� ���� ����
	void CreateIndexBuffer(const vector<UINT32>& buffer);

};

