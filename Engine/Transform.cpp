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
	//TransformParams ����ü �ʱ�ȭ = 0���� �б�
	TransformParams transformParams = {};

	//���� ��� ����
	transformParams.matWorld = matrixWorld;

	//ī�޶��� �� ��� ����(Camera Ŭ���� ���� �� ��� ���� ���)
	transformParams.matView = Camera::StaticMatrixView;
	//ī�޶��� ���� ��� ����(Camera Ŭ���� ���� ���� ��� ���� ���)
	transformParams.matProjection = Camera::StaticMatrixProjection;

	//����-�� ��� ��� �� ����(���� ��� * �� ���)
	transformParams.matWV = matrixWorld * Camera::StaticMatrixView;

	//����-��-���� ��� ��� �� ����(���� ��� * �� ��� * ���� ���)
	transformParams.matWVP = matrixWorld * Camera::StaticMatrixView * Camera::StaticMatrixProjection;

	//��� ���ۿ� ��ȯ ��Ʈ���� �����͸� Ǫ��
	GameEngine::Get().GetConstantBuffer(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&transformParams, sizeof(transformParams));
}
