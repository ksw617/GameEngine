#include "pch.h"
#include "Input.h"

void Input::Init(HWND _hwnd)
{
	hwnd = _hwnd; // ������ �ڵ� ���

	//Ű ���� ���͸� �ʱ�ȭ �ϰ� ��� Ű ���¸� NONE���� ����
	states.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
}

void Input::Update()
{
	//���� Ȱ��ȭ�� ������ �ڵ��� ������
	HWND activeHwnd = GetActiveWindow();
						  
	//�Է��� ���� ������ Ȱ��ȭ�� �����찡 �ƴ϶��
	if (hwnd != activeHwnd)
	{
		//��� Ű ���¸� NONE���� ����
		for (UINT32 key = 0; key < KEY_TYPE_COUNT; key++)
		{
			states[key] = KEY_STATE::NONE;
		}

		return;
	}

	//���� Ű���� ���¸� ���� �ֵ�
	BYTE asciiKeys[KEY_TYPE_COUNT] = {};

	//Ű���� ���� ���
	if (GetKeyboardState(asciiKeys) == false)
		return;

	//��� Ű Ÿ���� ��ȸ�ϸ� ���¸� ������Ʈ
	for (UINT32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		//Ű ���¸� ������
		KEY_STATE& state = states[key];

		//Ű�� ���� �ִ� Ȯ��
		if (asciiKeys[key] & 0x80)
		{
			//���� ������ Ű�� ���� ���¶�� PRESS, �׷��� ������ DOWN
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
			{
				state = KEY_STATE::PRESS;
			}
			else
			{

				//Ű�� �� ���� ���¶��
				state = KEY_STATE::DOWN;
			}

		}
		else  // Ű�� ���� ���� ���� ���¶��
		{

			//���� �����ӿ��� Ű�� ���� ���¶�� UP, �׷��� ������ NONE
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
			{
				state = KEY_STATE::UP;
			}
			else
			{
				state = KEY_STATE::NONE;
			}
		}
	}
}
