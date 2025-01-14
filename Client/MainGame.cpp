#include "pch.h"
#include "MainGame.h"
#include <GameEngine.h>
#include <SceneManager.h>

void MainGame::Init(HWND hwnd, int width, int height, bool windowed)
{
	GameEngine::Get().Init(hwnd, width, height, windowed);

	//씬 불러오는거 테스트 
	SceneManager::Get().LoadScene(L"SampleScene");
}

void MainGame::Update()
{
	GameEngine::Get().Update();
}
