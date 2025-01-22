#pragma once
#include "Component.h"

//LIGHT_TYPE 열거형 정의  : 조명의 유형을 나타냄
enum class LIGHT_TYPE : UINT8
{
	DIRECTIONAL_LIGHT,	// 방향성 조명
	POINT_LIGHT,		// 포인트 조명
	SPOT_LIGHT,			// 스팟 조명

};

//LightColor 구조체 정의 : 조명의 색상 속성들을 포함
struct LightColor
{
	Vector4 diffuse;	// 확산광 색상
	Vector4 ambient;	// 주변광 색상
	Vector4 specular;	// 반사광 색상
};

//LightInfo 구조체 정의 : 조명의 속성들을 포함
struct LightInfo
{										//d +a +s
	LightColor color;	//조명 색상		//16+16+16 byte	     //16 + 16 + 16
	Vector4 position;	//조명 위치		//16 byte			 // + 16
	Vector4 direction;	//조명 방향		//16 byte			 // + 16
	INT32 lightType;	//조명 타입		//4 byte
	float range;		//조명 범위		//4 byte
	float angle;		//조명 각도		//4 byte  // 12byte
	INT32 padding;		//패딩		    //4 byte			 // + 16

};

//LightParams 구조체 정의 : 다수의 조명 정보를 포함
struct LightParams
{
	UINT32 lightCount;		//조명 갯수		//4 byte
	Vector3 padding;		//공간      		//12 byte		 // 16byte
	LightInfo lights[50];	//조명 정보 배열 //16 byte * 50

};

//Component 상속
class Light : public Component
{
public:
	Light() : Component(COMPONENT_TYPE::LIGHT) {} // 생성자
	virtual ~Light() {} // 소멸자
private:
	LightInfo lightInfo = {};	// 조명 정보 초기화
private:
	//Vector3를 Vector4로 변환
	Vector4 Vec3ToVec4(const Vector3& vec3) { return Vector4(vec3.x, vec3.y, vec3.z, 0.0f); }
public:
	//Get 함수
	//조명 정보
	const LightInfo& GetLightInfo() { return lightInfo; }
public:
	//Set 함수
	//조명 방향 설정
	void SetLightDirection(const Vector3& direction) { lightInfo.direction = Vec3ToVec4(direction); }
	//확산광 색상 설정
	void SetDiffuse(const Vector3& diffuse) { lightInfo.color.diffuse = Vec3ToVec4(diffuse); }
	//주변광 색상 설정
	void SetAmbient(const Vector3& ambient) { lightInfo.color.ambient = Vec3ToVec4(ambient); }
	//반사광 색상 설정
	void SetSpecular(const Vector3& specular) { lightInfo.color.specular = Vec3ToVec4(specular); }
	//조명 타입 설정
	void SetLightType(LIGHT_TYPE type) { lightInfo.lightType = static_cast<INT32>(type); }
	//조명 범위	설정
	void SetLightRange(float range) { lightInfo.range = range; }
	//조명 각도 설정 
	void SetLightAngle(float angle) { lightInfo.angle = angle; }
public:
	//최종 업데이트 함수(Component 클라스 virtual 오버라이드)
	virtual void FinalUpdate() override;


};

