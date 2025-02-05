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

		//CullingMask 적용 유무 체크
		if (gameObject->GetCullingMask())
		{
			//게임오브젝트의 중심값을 가져오기
			Vector3 center = gameObject->GetTransform()->GetWorldPosition();

			//게임오브젝트의 x,y,z중 가장큰 크기값을 가져오기
			float radius = gameObject->GetTransform()->GetBoundingSphereRadius();

			//해당 구가 컬링에 포함되지 않는다면 그려주지 않기
			if (!occlusionCulling.ContainSphere(center, radius))
				continue;
		}

		gameObject->GetMeshFilter()->Render();

	}
}
