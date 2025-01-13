#pragma once


enum class COMPONENT_TYPE : UINT8
{
	TRANSFORM,		
	MESH_FILTER,	

	END,			

};

enum 
{
	FIXED_COMPONENT_COUNT = static_cast<UINT8>(COMPONENT_TYPE::END)
};

class Transform;
class GameObject;

class Component
{
public:
	Component(COMPONENT_TYPE _type);
	virtual ~Component();
protected:
	COMPONENT_TYPE type; 
	weak_ptr<GameObject> gameObject;	
private:
	friend GameObject;
	void SetGameObject(shared_ptr<GameObject> _gameObject) { gameObject = _gameObject; }
public:
	//���۳�Ʈ Ÿ���� ��ȯ���ִ� Get �Լ�
	COMPONENT_TYPE GetType() const { return type; }
	//���۳�Ʈ�� ��� �ִ� ���ӿ�����Ʈ�� ��ȿ���� Ȯ�� �ϴ� �Լ�
	bool IsValid() { return gameObject.expired() == false; }
public:
	//Start���� �ѹ� ȣ��
	virtual void Awake() {}
	//Update ������ �ѹ� ȣ��
	virtual void Start() {}
	//�� ������ ���� ������Ʈ �Ǵ� �Լ�
	virtual void Update() {}
	//�� ������ �Ĺݿ� ������Ʈ �Ǵ� �Լ�
	virtual void LateUpdate() {}
public:
	//GameObject Get�Լ�
	shared_ptr<GameObject> GetGameObject();
	//Transform Get�Լ�
	shared_ptr<Transform> GetTransfrom();
};

