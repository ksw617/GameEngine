#pragma once

//Object Ÿ���� �����ϴ� ������
enum class OBJECT_TYPE : UINT8
{
	NONE, // �⺻��
	GAMEOBJECT, // ���� ������Ʈ
	COMPONENT,	// ������Ʈ
	MATERIAL,	// ���׸���
	MESH,		// �Ž�
	SHADER,		// ���̴�
	TEXTURE,	// �ؽ�ó


	END,		//��
};

//Object Ÿ���� ������ ����
enum 
{
	OBJECT_TYPE_COUNT = static_cast<UINT8>(OBJECT_TYPE::END)

};

class Object
{
protected:
	OBJECT_TYPE type = OBJECT_TYPE::NONE;	//Object�� Ÿ��
	wstring name;							//Object�� �̸�
public:
	//������ : Object Ÿ���� ����
	Object(OBJECT_TYPE _type) : type(_type) {}

	//�Ҹ���
	virtual ~Object() {}
public:
	//Ÿ�� ��ȯ�ϴ� Get�Լ�
	OBJECT_TYPE GetType() const { return type; }
	//�̸� ��ȯ�ϴ� Get�Լ�
	const wstring& GetName() { return name; }
public:
	//�̸� ���� Set�Լ�
	void SetName(const wstring& _name) { name = _name; }
protected:
	//��ü�� �ε��ϴ� ���� �Լ�
	virtual void Load(const wstring& path) {}
	//��ü�� �����ϴ� ���� �Լ�
	virtual void Save(const wstring& path) {}
};

