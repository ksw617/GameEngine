#pragma once
#include "Component.h" // Component �Ӽ� ��� �ޱ� ���ؼ�

//��ȯ ����� �����ϴ� ����ü
struct TransformMatrix
{
	XMFLOAT4 offset;
};

class Transform	: public Component	//Component ���
{
public:
	//������
	//������Ʈ Ÿ���� TRANSFORM���� �����Ͽ� Component ������ ȣ��
	Transform() : Component(COMPONENT_TYPE::TRANSFORM) {}

	//�Ҹ���
	virtual ~Transform() {}
};

