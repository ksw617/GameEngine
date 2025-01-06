#pragma once

//컴포넌트 타이을 정의하는 열거형
enum class COMPONENT_TYPE : UINT8
{
	TRANSFORM,		//변환 컴포넌트
	MESH_FILTER,	//메쉬 필터 컴포넌트

	//.... 추가예정
	END,			//컴포넌트 타입의 끝

};

enum 
{
	//고정 컴포넌트 갯수를 정의
	FIXED_COMPONENT_COUNT = static_cast<UINT8>(COMPONENT_TYPE::END) // 컴포넌트 타입의 총 갯수

};

//GameObject전방선언
class GameObject;

class Component
{
public:
	//컴포넌트 생성자
	Component(COMPONENT_TYPE _type);

	//컴포넌트 소멸자
	virtual ~Component();
protected:
	COMPONENT_TYPE type; // 컴포넌트 타입

	weak_ptr<GameObject> gameObject;		// 이 컴포넌트가 속한 게임 객체
private:

	//GameObject 클라스가 private 맴버에 접근 할수 있도록 설정
	friend GameObject;

	//GameObject Set해주는 함수
	void SetGameObject(shared_ptr<GameObject> _gameObject) { gameObject = _gameObject; }

};

