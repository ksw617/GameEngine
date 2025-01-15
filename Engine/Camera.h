#pragma once
#include "Component.h"

enum class PROJECTION_TYPE : UINT8
{
	PERSEPECTIVE,		
	ORTHOGRAPHIC,		

};

class Camera : public Component
{
private:
	PROJECTION_TYPE type = PROJECTION_TYPE::PERSEPECTIVE;

	float nearView = 0.3f;	
	float farView = 1000.f;
	float fov = XM_PI / 4.f;
	float size = 1.f;		

	Matrix matrixView = {};			
	Matrix matrixProjection = {};	

public:
	static Matrix StaticMatrixView;			
	static Matrix StaticMatrixProjection;	
public:
	Camera();
	virtual ~Camera();

public:
	virtual void FinalUpdate() override;
public:
	//Render �Լ� �߰�
	void Render();
};

