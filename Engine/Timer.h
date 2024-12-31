#pragma once
class Timer
{
private:
	UINT64 frequency = 0;	// Ÿ�̸��� �󵵸� ��Ÿ��
	UINT64 prevCount = 0;	// ���� ī��Ʈ ��
	float deltaTime = 0.f;	// ������ �� �ð� ����
private:
	UINT32 frameCount = 0;	// ������ ī��Ʈ
	float frameTime = 0.f;	// ������ �ð� ������
	UINT32 fps = 0;			// �ʴ� ������ ��(Frame Per Second)
public:
	//���� FPS ���� ��ȯ�ϴ� �Լ�
	UINT32 GetFPS() const { return fps; }
	//������ �� �ð� ������ ��ȯ �ϴ� �Լ�
	float GetDeltaTime() const { return deltaTime; }
public:
	//Ÿ�̸� �ʱ�ȭ �Լ�
	void Init();

	//Ÿ�̸� ������Ʈ �Լ�(�� ������ ���� ȣ��)
	void Update();
};

