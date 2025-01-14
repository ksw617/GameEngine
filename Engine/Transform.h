#pragma once
#include "Component.h"

class Transform	: public Component
{
private:
	//부모를 기준으로 변환 정보들을 계산
	Vector3 localPosition = {}; //로컬 위치
	Vector3 localRotation = {}; //로컬 회전
	Vector3 localScacle = { 1.f, 1.f, 1.f };//로컬 크기(기본값 : 1.f, 1.f, 1.f)

	Matrix matrixLocal = {};	//로컬 변환 행렬
	Matrix matrixWorld = {};	//월드 변환 행렬

	weak_ptr<Transform> parent; // 부모 Transform을 가르키는 weak_ptr
public:
	Transform() : Component(COMPONENT_TYPE::TRANSFORM) {}
	virtual ~Transform() {}

public:
	//최종 업데이트 함수(매 프리임 마다 마지막에 호출됨)
	virtual void FinalUpdate() override;
};

