#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "Mesh.h"  
#include "Shader.h"	
#include "ConstantBuffer.h"  
#include "TableDescriptor.h"
#include "Texture.h" 
#include "DepthStencilBuffer.h" 
#include "Input.h"  
#include "Timer.h" 

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
	shared_ptr<TableDescriptor> tableDesc;
	shared_ptr<DepthStencilBuffer> depthStencilBuffer;
	shared_ptr<Input> input; 
	shared_ptr<Timer> timer;
	vector<shared_ptr<ConstantBuffer>> constBuffers;
public:
	shared_ptr<Device> GetDevice() { return device; }
	shared_ptr<CommandQueue> GetCmdQueue() { return commandQueue; }
	shared_ptr<SwapChain> GetSwapChain() { return swapChain; }
	shared_ptr<RootSignature> GetRootSignature() { return rootSignature; }
	shared_ptr<TableDescriptor> GetTableDesc() { return tableDesc; }
	shared_ptr<DepthStencilBuffer> GetDepthStencilBuffer() { return depthStencilBuffer; }
	shared_ptr<Input> GetInput() { return input; }
	shared_ptr<Timer> GetTimer() { return timer; }

	shared_ptr<ConstantBuffer> GetConstantBuffer(CONSTANT_BUFFER_TYPE type) { return constBuffers[static_cast<UINT8>(type)]; }
public:
	//Get함수
	//화면 크기 받아오기
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

public:
	void Init(HWND _hwnd, int _width, int _height, bool _windowed);
	void Render();

public:
	void Update();
	void ShowFPS(); 
	void CreateConstantBuffer(CBV_REGISTER reg, UINT32 bufferSize, UINT32 count);

public:
	void RenderBegin();
	void RenderEnd();
	void ResizeWindow(int _width, int _height);
};

