#pragma once

class GameObject;

class Scene
{
private:
	vector <shared_ptr<GameObject>> gameObjects;
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();
public:
	//Scene�� �ִ� ��� GameObject�鿡�� �����ϱ� ����
	const vector<shared_ptr<GameObject>>& GetGameObjets() { return gameObjects; }
public:
	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);
};

