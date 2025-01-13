#pragma once
#include "Component.h" // Component 속성 상속 받기 위해서

//변환 행렬을 저장하는 구조체
struct TransformMatrix
{
	XMFLOAT4 offset;
};

class Transform	: public Component	//Component 상속
{
public:
	//생성자
	//컴포넌트 타입을 TRANSFORM으로 설정하여 Component 생성자 호출
	Transform() : Component(COMPONENT_TYPE::TRANSFORM) {}

	//소멸자
	virtual ~Transform() {}
};

