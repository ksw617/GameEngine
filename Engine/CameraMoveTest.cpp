#include "pch.h"
#include "CameraMoveTest.h"
#include "Transform.h"
#include "GameEngine.h"

void CameraMoveTest::LateUpdate()
{
	//현재위치를 가져움
	Vector3 pos = GetTransfrom()->GetLocalPosition();

	//W키를 눌렀을 때 카메라를 앞으로 이동
	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::W))
		pos += GetTransfrom()->GetLook() * speed * GameEngine::Get().GetTimer()->GetDeltaTime();

	//S키를 눌렀을 때 카메라를 뒤로 이동
	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::S))
		pos -= GetTransfrom()->GetLook() * speed * GameEngine::Get().GetTimer()->GetDeltaTime();

	//A키를 눌렀을 때 카메라를 왼쪽 으로 이동
	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::A))
		pos -= GetTransfrom()->GetRight() * speed * GameEngine::Get().GetTimer()->GetDeltaTime();

	//D키를 눌렀을 때 카메라를 오른쪽 으로 이동
	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::D))
		pos += GetTransfrom()->GetRight() * speed * GameEngine::Get().GetTimer()->GetDeltaTime();

	//Q키를 눌렀을 때 카메라를 위로 회전
	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::Q))
	{
		//현재 회전값을 받아와서 X축 회전을 증가시킴
		Vector3 rotation = GetTransfrom()->GetLocalRotation();
		rotation.x += GameEngine::Get().GetTimer()->GetDeltaTime() * 0.5f;
		GetTransfrom()->SetLocalRotation(rotation);
	}

	//E키를 눌렀을 때 카메라를 아래로 회전
	if (GameEngine::Get().GetInput()->GetButton(KEY_TYPE::E))
	{
		//현재 회전값을 받아와서 X축 회전을 감소시킴
		Vector3 rotation = GetTransfrom()->GetLocalRotation();
		rotation.x -= GameEngine::Get().GetTimer()->GetDeltaTime() * 0.5f;
		GetTransfrom()->SetLocalRotation(rotation);

	}

	//변경된 위치로 설정
	GetTransfrom()->SetLocalPosition(pos);

}
