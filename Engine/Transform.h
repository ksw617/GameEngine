#pragma once
#include "Component.h"

class Transform : public Component
{
private:
	Vector3 localPosition = {};
	Vector3 localRotation = {};
	Vector3 localScale = { 1.f, 1.f, 1.f };

	Matrix matrixLocal = {};
	Matrix matrixWorld = {};

	weak_ptr<Transform> parent;
public:
	Transform() : Component(COMPONENT_TYPE::TRANSFORM) {}
	virtual ~Transform() {}
public:
	Vector3 GetLocalPosition() const { return localPosition; }
	Vector3 GetLocalRotation() const { return localRotation; }
	Vector3 GetLocalScale() const { return localScale; }
	Matrix GetLocalToWorldMatrix() const { return matrixWorld; }
	Vector3 GetWorldPosition() const { return matrixWorld.Translation(); }
	Vector3 GetRight() const { return matrixWorld.Right(); }
	Vector3 GetUp() const { return matrixWorld.Up(); }
	Vector3 GetLook() const { return matrixWorld.Backward(); }
	weak_ptr<Transform> GetParent() { return parent; }


	//크기값에서 x,y,z중에 가장 큰 값이 반지름으로 반환
	float GetBoundingSphereRadius() const { return max(max(localScale.x, localScale.y), localScale.z); }

public:
	void SetParent(shared_ptr<Transform> _parent) { parent = _parent; }
	void SetLocalPosition(const Vector3 position) { localPosition = position; }
	void SetLocalRotation(const Vector3 rotation) { localRotation = rotation; }
	void SetLocalScale(const Vector3 scale) { localScale = scale; }

public:
	virtual void FinalUpdate() override;
public:
	void PushData();
};

