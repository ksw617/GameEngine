#pragma once
#include "Component.h"

class Transform	: public Component
{
private:
	//�θ� �������� ��ȯ �������� ���
	Vector3 localPosition = {}; //���� ��ġ
	Vector3 localRotation = {}; //���� ȸ��
	Vector3 localScacle = { 1.f, 1.f, 1.f };//���� ũ��(�⺻�� : 1.f, 1.f, 1.f)

	Matrix matrixLocal = {};	//���� ��ȯ ���
	Matrix matrixWorld = {};	//���� ��ȯ ���

	weak_ptr<Transform> parent; // �θ� Transform�� ����Ű�� weak_ptr
public:
	Transform() : Component(COMPONENT_TYPE::TRANSFORM) {}
	virtual ~Transform() {}

public:
	//���� ������Ʈ �Լ�(�� ������ ���� �������� ȣ���)
	virtual void FinalUpdate() override;
};

