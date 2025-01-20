#pragma once
#include "Singleton.h" //ȣ��
class Scene;

class SceneManager : public Singleton<SceneManager>
{
	//Singleton Ŭ�󽺰� private �����ڿ� �����Ҽ� �ְ�
	friend class Singleton<SceneManager>;
private:
	SceneManager() = default;
	~SceneManager() = default;
private:
	shared_ptr<Scene> currentScene;

public:
	shared_ptr<Scene> GetCurrentScene() { return currentScene; }

public:
	void LoadScene(wstring sceneName);
	void Update();
	void Render();


private:
	shared_ptr<Scene> LoadSampleScene();
};

