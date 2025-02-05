#pragma once
#include "Component.h" 

class Transform;
class MeshFilter;
class Camera;
class Light;	
class MonoBehaviour;

class GameObject : public enable_shared_from_this<GameObject>, public Object 
{
private:
	//�ø� ����ũ ���� ����
	bool isCullingMask = true;
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> components;
	vector<shared_ptr<MonoBehaviour>> scripts;	
public:
	GameObject();
	virtual ~GameObject();
public:
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();
public:
	shared_ptr<Transform> GetTransform();
	shared_ptr<MeshFilter> GetMeshFilter();
	shared_ptr<Camera> GetCamera();
	shared_ptr<Light> GetLight();	
	shared_ptr<Component> GetFixedComponent(COMPONENT_TYPE type);

	//isCullingMask Get �Լ�
	bool GetCullingMask() const { return isCullingMask; }

public:
	//isCullingMask Set �Լ�
	void SetCullingMask(bool enable) { isCullingMask = enable; }
public:
	void AddComponent(shared_ptr<Component> component);

};

