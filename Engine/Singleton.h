#pragma once

//Singleton ���ø� Ŭ�� ����
template<typename T>
class Singleton
{
public:
	//Singleton �ν��Ͻ� ��ȯ
	static T& Get()
	{
		static T instance;
		return instance;
	}
protected:
	Singleton() = default;
	virtual ~Singleton() = default;
public:
	//���� ������ ����
	Singleton(const Singleton&) = delete;
	//���� �Ҵ� ������ ����
	Singleton& operator=(const Singleton&) = delete;

};

