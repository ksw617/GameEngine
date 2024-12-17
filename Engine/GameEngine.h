#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "Mesh.h"   //추가
#include "Shader.h"	//추가

class GameEngine
{
public:
	static GameEngine& Get()
	{
		static GameEngine instance;
		return instance;
	}
private:
	GameEngine() = default;
	~GameEngine() = default;
public:
	GameEngine(const GameEngine&) = delete;
	GameEngine& operator=(const GameEngine&) = delete;

private:
	HWND hwnd; 
	int width; 
	int height;
	bool windowed;
private:
	D3D12_VIEWPORT viewPort = {};	
	D3D12_RECT scissorRect = {};	
private:
	shared_ptr<Device> device;				
	shared_ptr<CommandQueue> commandQueue;	
	shared_ptr<SwapChain> swapChain;		
	shared_ptr<RootSignature> rootSignature;
public:
	shared_ptr<Device> GetDevice() { return device; }
	shared_ptr<CommandQueue> GetCmdQueue() { return commandQueue; }
	shared_ptr<SwapChain> GetSwapChain() { return swapChain; }
	shared_ptr<RootSignature> GetRootSignature() { return rootSignature; }

public:
	void Init(HWND _hwnd, int _width, int _height, bool _windowed);
	void Render();

public:
	void RenderBegin();
	void RenderEnd();
	void ResizeWindow(int _width, int _height);
};

