#pragma once
#include "MonoBehaviour.h"
class CameraMoveTest : public MonoBehaviour
{
private:
	float speed = 100.f;
public:
	CameraMoveTest() {}
	virtual ~CameraMoveTest() {}
public:
	//LateUpdate �Լ� ȣ��
	virtual void LateUpdate() override;
};

