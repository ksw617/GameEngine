#pragma once

//������Ʈ Ÿ���� �����ϴ� ������
enum class COMPONENT_TYPE : UINT8
{
	TRANSFORM,		//��ȯ ������Ʈ
	MESH_FILTER,	//�޽� ���� ������Ʈ

	//.... �߰�����
	END,			//������Ʈ Ÿ���� ��

};

enum 
{
	//���� ������Ʈ ������ ����
	FIXED_COMPONENT_COUNT = static_cast<UINT8>(COMPONENT_TYPE::END) // ������Ʈ Ÿ���� �� ����

};

//GameObject���漱��
class GameObject;

class Component
{
public:
	//������Ʈ ������
	Component(COMPONENT_TYPE _type);

	//������Ʈ �Ҹ���
	virtual ~Component();
protected:
	COMPONENT_TYPE type; // ������Ʈ Ÿ��

	weak_ptr<GameObject> gameObject;		// �� ������Ʈ�� ���� ���� ��ü
private:

	//GameObject Ŭ�󽺰� private �ɹ��� ���� �Ҽ� �ֵ��� ����
	friend GameObject;

	//GameObject Set���ִ� �Լ�
	void SetGameObject(shared_ptr<GameObject> _gameObject) { gameObject = _gameObject; }

};

