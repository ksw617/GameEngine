#include "pch.h"
#include "Transform.h"
#include "Camera.h"
#include "GameEngine.h"

void Transform::FinalUpdate()
{
	Matrix matrixScale = Matrix::CreateScale(localScale);

	Matrix matrixRotation = Matrix::CreateRotationX(localRotation.x);
	matrixRotation *= Matrix::CreateRotationY(localRotation.y);
	matrixRotation *= Matrix::CreateRotationZ(localRotation.z);

	Matrix matrixTranslation = Matrix::CreateTranslation(localPosition);

	matrixLocal = matrixScale * matrixRotation * matrixTranslation;
	matrixWorld = matrixLocal;

	shared_ptr<Transform> myParent = GetParent().lock();

	if (myParent != nullptr)
	{
		matrixWorld *= myParent->GetLocalToWorldMatrix();
	}

}

void Transform::PushData()
{
	//���� - �� - ���� ��ȯ ��� ���
	Matrix mat = matrixWorld * Camera::StaticMatrixView * Camera::StaticMatrixProjection;

	//��ȯ ��� �����͸� ��� ���ۿ� ����
	GameEngine::Get().GetConstantBuffer(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&mat, sizeof(mat));
}
