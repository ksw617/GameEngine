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
	//weak_ptr 잠금하여 shared_ptr<GameObject>를 반환
	//값이 없을 경우 nullptr 반환
	return gameObject.lock();
}

shared_ptr<Transform> Component::GetTransfrom()
{
	//weak_ptr 잠금하여 shared_ptr<GameObject>를 반환
	//gameObject가 nullptr이 아니라면 gameObject의 transform 반환
	auto gameObj = gameObject.lock();
	return gameObj != nullptr ? gameObj->GetTransform() : nullptr;
}
