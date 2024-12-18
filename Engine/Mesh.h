#pragma once
class Mesh
{
private:
	ComPtr<ID3D12Resource> vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView = {};
	int vertexCount = 0;
	//��ġ, ȸ��, ũ��
	XMFLOAT4 transform = {};
public:
	void Init(vector<Vertex>& vec);
	void Render();

	//Set�Լ�
	void SetTransform(const XMFLOAT4& _transform) { transform = _transform; }
};

