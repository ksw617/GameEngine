#include "pch.h"
#include "Mesh.h"
#include "GameEngine.h"


void Mesh::Init(const vector<Vertex>& vertexBuffer, const vector<UINT32>& indexBuffer)
{
	//�־��� ���� ���� �����͸� ����Ͽ� ���� ���� ����
	CreateVertexBuffer(vertexBuffer);

	//�־��� �ε��� ���� �����͸� ����Ͽ� �ε��� ���� ����
	CreateIndexBuffer(indexBuffer);
}



void Mesh::CreateVertexBuffer(const vector<Vertex>& buffer)
{
	//���� Init�� �����
	vertexCount = static_cast<int>(buffer.size());
	int bufferSize = vertexCount * sizeof(Vertex);

	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	GameEngine::Get().GetDevice()->GetDevice()->CreateCommittedResource(
		&heapProperty, D3D12_HEAP_FLAG_NONE, &desc, D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&vertexBuffer));

	void* vertexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0);
	vertexBuffer->Map(0, &readRange, &vertexDataBuffer);
	memcpy(vertexDataBuffer, &buffer[0], bufferSize);
	vertexBuffer->Unmap(0, nullptr);

	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.StrideInBytes = sizeof(Vertex);
	vertexBufferView.SizeInBytes = bufferSize;
}

void Mesh::CreateIndexBuffer(const vector<UINT32>& buffer)
{
	//�ε��� ���� ����
	indexCount = static_cast<int>(buffer.size());
	//�ε��� ������ ũ��(����Ʈ ����) ���
	int bufferSize = indexCount * sizeof(UINT32);

	//�� �Ӽ� ����(���ε� ��)
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

	//���ҽ� ������ ����(����)
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	GameEngine::Get().GetDevice()->GetDevice()->CreateCommittedResource
	(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuffer)
	);

	//�ε��� �����͸� ���ۿ� ����
	void* indexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0); // �б� ���� ����
	indexBuffer->Map(0, &readRange, &indexDataBuffer); // ���� ����
	memcpy(indexDataBuffer, &buffer[0], bufferSize); // ������ ����
	indexBuffer->Unmap(0, nullptr); // ���� ���

	//�ε��� ���� �� ����
	indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress(); // GPU �����ּ� �޾ƿ���
	indexBufferView.Format = DXGI_FORMAT_R32_UINT; // �ε��� ���� ����(32��Ʈ ����)
	indexBufferView.SizeInBytes = bufferSize;      // ���� ũ�� ����
}

void Mesh::Render()
{
	GameEngine::Get().GetCmdQueue()->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GameEngine::Get().GetCmdQueue()->GetCmdList()->IASetVertexBuffers(0, 1, &vertexBufferView);

	//�ε��� ���� ���ε�
	GameEngine::Get().GetCmdQueue()->GetCmdList()->IASetIndexBuffer(&indexBufferView);

	GameEngine::Get().GetConstBuffer()->PushData(&transform, sizeof(transform));

	GameEngine::Get().GetTableDesc()->CommitTable();

	//�ε����� ����Ͽ� �׸���(DrawIndexedInstanced)
	GameEngine::Get().GetCmdQueue()->GetCmdList()->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
}
