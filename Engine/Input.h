#pragma once

//Ű Ÿ���� �����ϴ� ������ Ŭ��
enum class KEY_TYPE
{
	UP = VK_UP,			// ���� ���� Ű
	DOWN = VK_DOWN,		// �Ʒ��� ���� Ű
	LEFT = VK_LEFT,		// ���� ���� Ű
	RIGHT = VK_RIGHT,	// ������ ����Ű,

	W = 'W',			//'W' Ű
	A = 'A',			//'A' Ű
	S = 'S',			//'S' Ű
	D = 'D',			//'D' Ű

};

//Ű ���¸� �����ϴ� ������ Ŭ��
enum class KEY_STATE
{
	NONE,	// �ƹ� ���� �ƴ�
	PRESS,	// Ű�� ������ �ִ� ����
	DOWN,	// Ű�� ó�� ���� ����
	UP,		// Ű�� ������ �� ����
	END,	// ���� ��
};

//Ű�� ������ ������ ���� �ϴ� ������
enum
{
	KEY_TYPE_COUNT = static_cast<int>(UINT8_MAX + 1),	// Ű Ÿ���� �� ����
	KEY_STATE_COUNT = static_cast<int>(KEY_STATE::END),	// Ű ������ �� ����

};

class Input
{
private:
	HWND hwnd;	// ���� �ڵ�
	vector<KEY_STATE> states; // Ű ���¸� �����ϴ� ����

private:
	//Ű�� ���� ���¸� �������� �Լ�
	inline KEY_STATE GetState(KEY_TYPE key) { return states[static_cast<UINT8>(key)];	}

public:
	// Ű�� ������ �ִ��� Ȯ�� �ϴ� �Լ�
	bool GetButton(KEY_TYPE key)
	{ 
		return GetState(key) == KEY_STATE::PRESS; 
	}
	// Ű�� ó�� �������� Ȯ�� �ϴ� �Լ�
	bool GetButtonDown(KEY_TYPE key) { return GetState(key) == KEY_STATE::DOWN; }
	// Ű�� �����ٰ� �������� Ȯ�� �ϴ� �Լ�
	bool GetBottonUp(KEY_TYPE key) { return GetState(key) == KEY_STATE::UP; }

public:
	//�Է� Ŭ�󽺸� �ʱ�ȭ
	void Init(HWND _hwnd);

	//Ű ���¸� ������Ʈ �ϴ� �Լ�
	void Update();

};

