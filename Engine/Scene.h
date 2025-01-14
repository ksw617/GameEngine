#pragma once

class GameObject;

class Scene
{
private:
	//�� ���� GameObject���� �����ϴ� vector
	vector <shared_ptr<GameObject>> gameObjects;
public:
	//���� �Լ�
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
public:
	//GameObject �߰�
	void AddGameObject(shared_ptr<GameObject> gameObject);
	//GameObject ����
	void RemoveGameObject(shared_ptr<GameObject> gameObject);
};

