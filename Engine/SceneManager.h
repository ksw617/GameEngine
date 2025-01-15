#pragma once

class Scene;

class SceneManager
{
private:
	SceneManager() = default;
	~SceneManager() = default;
public:
	static SceneManager& Get()
	{
		static SceneManager instance;
		return instance;
	}

public:
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
private:
	shared_ptr<Scene> currentScene;

public:
	shared_ptr<Scene> GetCurrentScene() { return currentScene; }

public:
	void LoadScene(wstring sceneName);
	void Update();
	//Render 함수 추가
	void Render();


private:
	shared_ptr<Scene> LoadSampleScene();
};

