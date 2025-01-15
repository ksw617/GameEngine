#include "pch.h"
#include "Camera.h"
#include "GameEngine.h"
#include "Transform.h"
#include "Scene.h"			//Scene �߰�
#include "SceneManager.h"	//SceneManager �߰�
#include "GameObject.h"		//GameObject �߰�
#include "MeshFilter.h"		//MeshFilter �߰�

Matrix Camera::StaticMatrixView;
Matrix Camera::StaticMatrixProjection;

Camera::Camera() : Component(COMPONENT_TYPE::CAMERA)
{
}

Camera::~Camera()
{
}

void Camera::FinalUpdate()
{
	matrixView = GetTransfrom()->GetLocalToWorldMatrix().Invert();

	float width = static_cast<float>(GameEngine::Get().GetWidth());
	float height = static_cast<float>(GameEngine::Get().GetHeight());

	if (type == PROJECTION_TYPE::PERSEPECTIVE)
	{
		matrixProjection = XMMatrixPerspectiveFovLH(fov, width / height, nearView, farView);
	}
	else
	{
		matrixProjection = XMMatrixOrthographicLH(width * size, height * size, nearView, farView);
	}

	StaticMatrixView = matrixView;
	StaticMatrixProjection = matrixProjection;
}

void Camera::Render()
{
	//���� ���� ������
	shared_ptr<Scene> scene = SceneManager::Get().GetCurrentScene();

	//���� ���� ��� ���� ��ü�� ������
	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjets();

	//�� gameObject�� ��ȸ�ϸ� �ش� gameObejct�� ���� ó��
	for (auto& gameObject : gameObjects)
	{
		//gameObject�� MeshFilter�� ���� ��� �н�
		if (gameObject->GetMeshFilter() == nullptr)
			continue;

		//gameObject�� MeshFilter ������Ʈ Render�� ����
		gameObject->GetMeshFilter()->Render();

	}
}
