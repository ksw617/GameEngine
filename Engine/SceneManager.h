#pragma once
#include "Singleton.h" //호출
class Scene;

class SceneManager : public Singleton<SceneManager>
{
	//Singleton 클라스가 private 생성자에 접근할수 있게
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

