#pragma once
#include "Component.h"

//GameObject를 정의 하는 클ㄹ라스
class GameObject : public enable_shared_from_this<GameObject> 
{
private:
	//고정 컴포넌트들을 저장하는 배열
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> components;

public:
	//생성자
	GameObject();

	//소멸자
	virtual ~GameObject();

};

