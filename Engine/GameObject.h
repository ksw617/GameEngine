#pragma once

#include "Component.h"  // �߰�

//Transform ���漱��
//class Component;
class Transform;

class GameObject : public enable_shared_from_this<GameObject> 
{
private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> components;

public:
	GameObject();
	virtual ~GameObject();
public:
	void Init();
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
public:
	shared_ptr<Transform> GetTransform();
	void AddComponent(shared_ptr<Component> component);
};

