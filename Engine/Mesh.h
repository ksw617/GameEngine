#pragma once
class Mesh
{
private:
	//���� ���� ���ҽ��� �����ϴ� ����Ʈ ������
	ComPtr<ID3D12Resource> vertexBuffer;
	//���� ���� �� ����ü �ʱ�ȭ
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView = {};
	int vertexCount = 0; //���� ������ ����
public:
	//�־��� ���� ���͸� ����Ͽ� �Ž��� �ʱ�ȭ
	void Init(vector<Vertex>& vec);
	//�Ž��� ������
	void Render();
};

