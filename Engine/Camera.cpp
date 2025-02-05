#include "pch.h"
#include "Camera.h"
#include "GameEngine.h"
#include "Transform.h"
#include "Scene.h"			
#include "SceneManager.h"	
#include "GameObject.h"		
#include "MeshFilter.h"		

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

	occlusionCulling.FinalUpdate();
}

void Camera::Render()
{
	shared_ptr<Scene> scene = SceneManager::Get().GetCurrentScene();
	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjets();
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetMeshFilter() == nullptr)
			continue;

		//CullingMask ���� ���� üũ
		if (gameObject->GetCullingMask())
		{
			//���ӿ�����Ʈ�� �߽ɰ��� ��������
			Vector3 center = gameObject->GetTransform()->GetWorldPosition();

			//���ӿ�����Ʈ�� x,y,z�� ����ū ũ�Ⱚ�� ��������
			float radius = gameObject->GetTransform()->GetBoundingSphereRadius();

			//�ش� ���� �ø��� ���Ե��� �ʴ´ٸ� �׷����� �ʱ�
			if (!occlusionCulling.ContainSphere(center, radius))
				continue;
		}

		gameObject->GetMeshFilter()->Render();

	}
}
