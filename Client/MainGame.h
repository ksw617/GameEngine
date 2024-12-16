#pragma once

class MainGame
{
public:
	//초기화
	void Init(HWND hwnd, int width, int height, bool windowed);
	//프로그램 진행
	void Update();
};

