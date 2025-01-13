#include "pch.h"
#include "Component.h"
#include "GameObject.h"	 

Component::Component(COMPONENT_TYPE _type) : type(_type)
{
}

Component::~Component()
{
}

shared_ptr<GameObject> Component::GetGameObject()
{
	//weak_ptr ����Ͽ� shared_ptr<GameObject>�� ��ȯ
	//���� ���� ��� nullptr ��ȯ
	return gameObject.lock();
}

shared_ptr<Transform> Component::GetTransfrom()
{
	//weak_ptr ����Ͽ� shared_ptr<GameObject>�� ��ȯ
	//gameObject�� nullptr�� �ƴ϶�� gameObject�� transform ��ȯ
	auto gameObj = gameObject.lock();
	return gameObj != nullptr ? gameObj->GetTransform() : nullptr;
}
