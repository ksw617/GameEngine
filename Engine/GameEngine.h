#pragma once
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
	HWND hwnd; // ����� ������ �ڵ�
	int width; // ȭ�� �ʺ�
	int height;// ȭ�� ����
	bool windowed;// â��� ����(true : â���, false : ��üȭ��)
private:
	D3D12_VIEWPORT viewPort = {};	// ����Ʈ ����
	D3D12_RECT scissorRect = {};	// ����(Rect) ����
private:
	shared_ptr<class Device> device;				//Device Ŭ���� ����Ʈ ������
	shared_ptr<class CommandQueue> commandQueue;	//CommandQueue Ŭ���� ����Ʈ ������
	shared_ptr<class SwapChain> swapChain;				//SwapChain Ŭ���� ����Ʈ ������

public:
	//���� �ʱ�ȭ �Լ�
	void Init(HWND _hwnd, int _width, int _height, bool _windowed);

	//������ �Լ�
	void Render();

public:
	//������ ���� �Լ�
	void RenderBegin();
	//������ ���� �Լ�
	void RenderEnd();

	//������ ũ�� ���� �Լ�
	void ResizeWindow(int _width, int _height);
};

