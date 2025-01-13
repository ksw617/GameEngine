#pragma once
//Material 전방선언
class Material;

class Mesh
{
private:
	ComPtr<ID3D12Resource> vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView = {};
	UINT32 vertexCount = 0;
	
	ComPtr<ID3D12Resource> indexBuffer;		
	D3D12_INDEX_BUFFER_VIEW indexBufferView;
	UINT32 indexCount = 0;					

	//transform 제거
	//XMFLOAT4 transform = {};

	//Material 제거
	//shared_ptr<Material> material = {};
	
public:
	void Init(const vector<Vertex>& vertexBuffer, const vector<UINT32>& indexBuffer);
	void Render();

	//SetTransform 제거
	//void SetTransform(const XMFLOAT4& _transform) { transform = _transform; }
	//SetMaterial 제거
	//void SetMaterial(shared_ptr<Material> _material) { material = _material; }

private:
	void CreateVertexBuffer(const vector<Vertex>& buffer);
	void CreateIndexBuffer(const vector<UINT32>& buffer);

};

