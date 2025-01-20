#include "pch.h"
#include "CameraMoveTest.h"
#include "Transform.h"
#include "GameEngine.h"

void CameraMoveTest::LateUpdate()
{
	Vector3 pos = GetTransfrom()->GetLocalPosition();

	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::W))
		pos += GetTransfrom()->GetLook() * speed * GameEngine::Get().GetTimer()->GetDeltaTime();

	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::S))
		pos -= GetTransfrom()->GetLook() * speed * GameEngine::Get().GetTimer()->GetDeltaTime();

	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::A))
		pos -= GetTransfrom()->GetRight() * speed * GameEngine::Get().GetTimer()->GetDeltaTime();

	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::D))
		pos += GetTransfrom()->GetRight() * speed * GameEngine::Get().GetTimer()->GetDeltaTime();

	//RŰ�� ������ �� ī�޶� ���� ȸ��
	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::R))
	{
		//���� ȸ������ �޾ƿͼ� X�� ȸ���� ���ҽ�Ŵ
		Vector3 rotation = GetTransfrom()->GetLocalRotation();
		rotation.x -= GameEngine::Get().GetTimer()->GetDeltaTime() * 0.5f;
		GetTransfrom()->SetLocalRotation(rotation);
	}

	//FŰ�� ������ �� ī�޶� �Ʒ��� ȸ��
	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::F))
	{
		//���� ȸ������ �޾ƿͼ� X�� ȸ���� ������Ŵ
		Vector3 rotation = GetTransfrom()->GetLocalRotation();
		rotation.x += GameEngine::Get().GetTimer()->GetDeltaTime() * 0.5f;
		GetTransfrom()->SetLocalRotation(rotation);

	}

	//QŰ�� ������ �� ī�޶� ���� ȸ��
	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::Q))
	{
		//���� ȸ������ �޾ƿͼ� Y�� ȸ���� ���ҽ�Ŵ
		Vector3 rotation = GetTransfrom()->GetLocalRotation();
		rotation.y -= GameEngine::Get().GetTimer()->GetDeltaTime() * 0.5f;
		GetTransfrom()->SetLocalRotation(rotation);
	}

	//EŰ�� ������ �� ī�޶� �Ʒ��� ȸ��
	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::E))
	{
		//���� ȸ������ �޾ƿͼ� X�� ȸ���� ������Ŵ
		Vector3 rotation = GetTransfrom()->GetLocalRotation();
		rotation.y += GameEngine::Get().GetTimer()->GetDeltaTime() * 0.5f;
		GetTransfrom()->SetLocalRotation(rotation);

	}


	GetTransfrom()->SetLocalPosition(pos);

}
