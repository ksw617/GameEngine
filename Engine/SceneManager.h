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


private:
	//Test¿ë
	shared_ptr<Scene> LoadTestScene();
};

