#pragma once
#include "Component.h"

//GameObject�� ���� �ϴ� Ŭ����
class GameObject : public enable_shared_from_this<GameObject> 
{
private:
	//���� ������Ʈ���� �����ϴ� �迭
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> components;

public:
	//������
	GameObject();

	//�Ҹ���
	virtual ~GameObject();

};

