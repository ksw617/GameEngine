#include "pch.h"
#include "Timer.h"

void Timer::Init()
{
	//Ÿ�̸� �󵵸� ����� frequency ������ ����
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));

	//���� ī��Ʈ ���� ���� prevCount ������ ����(�ʱ�ȭ)
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&prevCount)); // CPU Ŭ��
}

void Timer::Update()
{
	//���� ī��Ʈ ��
	UINT64 currentCount;

	//���� ī��Ʈ ���� ���� currentCount ������ ����
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	//�� ������ ���� �ð� ����(deltaTime)�� ���
	deltaTime = (currentCount - prevCount) / static_cast<float>(frequency);

	//���� ī��Ʈ ���� prevCount�� ���� �����Ͽ� ���� �����ӿ� ����� �� �ְ� ��
	prevCount = currentCount;

	//������ ī��Ʈ�� ����
	frameCount++;

	//������ �ð� �������� deltaTime�� ����
	frameTime += deltaTime;
					   
	//������ ������ �ð��� 1�ʸ� �ʰ��ϸ� FPS ���
	if (frameTime > 1.f)
	{
		//FPS ��� : frameCount�� frameTime���� ������ �ʴ� ������ ���� ����
		fps = static_cast<UINT32>(frameCount / frameTime);

		//������ �ð��� ������ ī��Ʈ�� �ʱ�ȭ
		frameTime = 0.f;
		frameCount = 0;

	}
}
