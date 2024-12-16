#include "pch.h"
#include "MainGame.h"
#include <GameEngine.h>

void MainGame::Init(HWND hwnd, int width, int height, bool windowed)
{
	GameEngine::Get().Init(hwnd, width, height, windowed);
}

void MainGame::Update()
{
	GameEngine::Get().Render();
}
