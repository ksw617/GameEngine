#include "pch.h"
#include "Camera.h"
#include "GameEngine.h"
#include "Transform.h"
#include "Scene.h"			//Scene 추가
#include "SceneManager.h"	//SceneManager 추가
#include "GameObject.h"		//GameObject 추가
#include "MeshFilter.h"		//MeshFilter 추가

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
	//현재 씬을 가져옴
	shared_ptr<Scene> scene = SceneManager::Get().GetCurrentScene();

	//현재 씬의 모든 게임 객체를 가져옴
	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjets();

	//각 gameObject를 순회하며 해당 gameObejct에 대한 처리
	for (auto& gameObject : gameObjects)
	{
		//gameObject에 MeshFilter가 없는 경우 패스
		if (gameObject->GetMeshFilter() == nullptr)
			continue;

		//gameObject의 MeshFilter 컴포넌트 Render를 실행
		gameObject->GetMeshFilter()->Render();

	}
}
