#include "pch.h"
#include "Resources.h"

shared_ptr<Mesh> Resources::LoadCubeMesh()
{
	//�̹� "Cube"��� Ű�� �ε�� �Ž��� �ִ� Ȯ��
	shared_ptr<Mesh> findMesh = GetResource<Mesh>(L"Cube");

	//�̹� ������ ��ȯ
	if (findMesh)
		return findMesh;

	//ť�� ���� ũ�� ����
	float wHalf = 0.5f; //�ʺ�
	float hHalf = 0.5f;	//����
	float dHalf = 0.5f; //����

	//���� �迭 ����(24���� ����) : �� ������
	vector<Vertex> vec(24);

	//�ո� ���� ����
	vec[0] = Vertex(Vector3(-wHalf, -hHalf, -dHalf), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f, 0.0f, 0.0f));
	vec[1] = Vertex(Vector3(-wHalf, +hHalf, -dHalf), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f, 0.0f, 0.0f));
	vec[2] = Vertex(Vector3(+wHalf, +hHalf, -dHalf), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f, 0.0f, 0.0f));
	vec[3] = Vertex(Vector3(+wHalf, -hHalf, -dHalf), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, -1.0f), Vector3(1.0f, 0.0f, 0.0f));

	//�޸� ���� ����
	vec[4] = Vertex(Vector3(-wHalf, -hHalf, +dHalf), Vector2(1.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f));
	vec[5] = Vertex(Vector3(+wHalf, -hHalf, +dHalf), Vector2(0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f));
	vec[6] = Vertex(Vector3(+wHalf, +hHalf, +dHalf), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f));
	vec[7] = Vertex(Vector3(-wHalf, +hHalf, +dHalf), Vector2(1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f));

	//���� ���� ����
	vec[8]  = Vertex(Vector3(-wHalf, +hHalf, -dHalf), Vector2(0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
	vec[9]  = Vertex(Vector3(-wHalf, +hHalf, +dHalf), Vector2(0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
	vec[10] = Vertex(Vector3(+wHalf, +hHalf, +dHalf), Vector2(1.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));
	vec[11] = Vertex(Vector3(+wHalf, +hHalf, -dHalf), Vector2(1.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f));

	//�Ʒ��� ���� ����
	vec[12] = Vertex(Vector3(-wHalf, -hHalf, -dHalf), Vector2(1.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f));
	vec[13] = Vertex(Vector3(+wHalf, -hHalf, -dHalf), Vector2(0.0f, 1.0f), Vector3(0.0f, -1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f));
	vec[14] = Vertex(Vector3(+wHalf, -hHalf, +dHalf), Vector2(0.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f));
	vec[15] = Vertex(Vector3(-wHalf, -hHalf, +dHalf), Vector2(1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f));

	//���ʸ� ���� ����
	vec[16] = Vertex(Vector3(-wHalf, -hHalf, +dHalf), Vector2(0.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f));
	vec[17] = Vertex(Vector3(-wHalf, +hHalf, +dHalf), Vector2(0.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f));
	vec[18] = Vertex(Vector3(-wHalf, +hHalf, -dHalf), Vector2(1.0f, 0.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f));
	vec[19] = Vertex(Vector3(-wHalf, -hHalf, -dHalf), Vector2(1.0f, 1.0f), Vector3(-1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f));

	//�����ʸ� ���� ����
	vec[20] = Vertex(Vector3(+wHalf, -hHalf, -dHalf), Vector2(0.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
	vec[21] = Vertex(Vector3(+wHalf, +hHalf, -dHalf), Vector2(0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
	vec[22] = Vertex(Vector3(+wHalf, +hHalf, +dHalf), Vector2(1.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
	vec[23] = Vertex(Vector3(+wHalf, -hHalf, +dHalf), Vector2(1.0f, 1.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));

	//�ε��� �迭 ���� (36���� �ε���)
	vector<UINT32> idx(36);

	//�ո� �ε��� ����
	idx[0] = 0; idx[1] = 1; idx[2] = 2;
	idx[3] = 0; idx[4] = 2; idx[5] = 3;

	//�޸� �ε��� ����
	idx[6] = 4; idx[7] = 5; idx[8] = 6;
	idx[9] = 4; idx[10] = 6; idx[11] = 7;

	//���� �ε��� ����
	idx[12] = 8; idx[13] = 9; idx[14] = 10;
	idx[15] = 8; idx[16] = 10; idx[17] = 11;

	//�Ʒ��� �ε��� ����
	idx[18] = 12; idx[19] = 13; idx[20] = 14;
	idx[21] = 12; idx[22] = 14; idx[23] = 15;

	//���ʸ� �ε��� ����
	idx[24] = 16; idx[25] = 17; idx[26] = 18;
	idx[27] = 16; idx[28] = 18; idx[29] = 19;

	//�����ʸ� �ε��� ����
	idx[30] = 20; idx[31] = 21; idx[32] = 22;
	idx[33] = 20; idx[34] = 22; idx[35] = 23;

	//���ο� �Ž� ��ü�� �����ϰ�
	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	//�ʱ�ȭ
	mesh->Init(vec, idx);

	//"Cube"��� Ű�� �Ž��� ���ҽ��� �߰�
	Add(L"Cube", mesh);

	return mesh; // �Ž� ��ȯ

}
