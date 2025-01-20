#include "pch.h"
#include "Component.h"
#include "GameObject.h"	 

//타입 초기화
Component::Component(COMPONENT_TYPE _type) : type(_type), Object(OBJECT_TYPE::COMPONENT)
{
}

Component::~Component()
{
}

shared_ptr<GameObject> Component::GetGameObject()
{
	return gameObject.lock();
}

shared_ptr<Transform> Component::GetTransfrom()
{
	auto gameObj = gameObject.lock();
	return gameObj != nullptr ? gameObj->GetTransform() : nullptr;
}
