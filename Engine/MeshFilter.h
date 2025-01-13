#pragma once
#include "Component.h"

class Mesh;
class Material;

//Component ���
class MeshFilter : public Component
{
private:
	//Mesh �����͸� ����Ű�� ����Ʈ ������
	shared_ptr<Mesh> mesh;
	//Material �����͸� ����Ű�� ����Ʈ ������
	shared_ptr<Material> material;

public:
	//������
	//������Ʈ Ÿ���� MESH_FILTER�� �����Ͽ� Component ������ ȣ��
	MeshFilter() : Component(COMPONENT_TYPE::MESH_FILTER) {}
	//�Ҹ���
	virtual ~MeshFilter() {}
public:
	//Mesh set�Լ�
	void SetMesh(shared_ptr<Mesh> _mesh) { mesh = _mesh; }

	//Material set �Լ�
	void SetMaterial(shared_ptr<Material> _mat) { material = _mat; }

public:
	//������ �Լ�
	void Render();
	//�� ������ ������Ʈ �Ҷ� ���� {������ �Լ� ����()}
	virtual void Update() override { Render(); }
};

