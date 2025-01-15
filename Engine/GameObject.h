#pragma once
#include "Component.h" 

class Transform;

//���� ����
class MeshFilter;
class Camera;

class MonoBehaviour;

class GameObject : public enable_shared_from_this<GameObject> 
{
private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> components;
	vector<shared_ptr<MonoBehaviour>> scripts;	
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
	void FinalUpdate();
public:
	shared_ptr<Transform> GetTransform();

	//MeshFilter Get �Լ�
	shared_ptr<MeshFilter> GetMeshFilter();

	//Camera Get �Լ�
	shared_ptr<Camera> GetCamera();

	//�ʿ��� ������Ʈ�鸸 ��ȯ
	shared_ptr<Component> GetFixedComponent(COMPONENT_TYPE type);

public:
	void AddComponent(shared_ptr<Component> component);

};

