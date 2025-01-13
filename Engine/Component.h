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
	//컴퍼넌트 타입을 반환해주는 Get 함수
	COMPONENT_TYPE GetType() const { return type; }
	//컴퍼넌트를 들고 있는 게임오브젝트가 유효한지 확인 하는 함수
	bool IsValid() { return gameObject.expired() == false; }
public:
	//Start전에 한번 호출
	virtual void Awake() {}
	//Update 이전에 한번 호출
	virtual void Start() {}
	//매 프레임 마다 업데이트 되는 함수
	virtual void Update() {}
	//매 프레임 후반에 업데이트 되는 함수
	virtual void LateUpdate() {}
public:
	//GameObject Get함수
	shared_ptr<GameObject> GetGameObject();
	//Transform Get함수
	shared_ptr<Transform> GetTransfrom();
};

