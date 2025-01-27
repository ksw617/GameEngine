#pragma once

enum class CONSTANT_BUFFER_TYPE : UINT8
{
	GLOBAL,		// 전역 데이터 관리
	TRANSFORM,	
	MATERIAL,	
	END,	

};

enum
{
	CONSTANT_BUFFER_COUNT = static_cast<UINT8>(CONSTANT_BUFFER_TYPE::END), // 상수 버퍼 타입의 총 갯수
};

class ConstantBuffer
{
private:
	ComPtr<ID3D12Resource> cbvBuffer;
	BYTE* mappedBuffer = nullptr;

	UINT32 elementSize = 0;
	UINT32 elementCount = 0;
	UINT32 currentIndex = 0;
private:
	ComPtr<ID3D12DescriptorHeap> cbvDescHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandleBegin = {};
	UINT32 handleIncrementSize = 0;
	CBV_REGISTER cbvRegister = {};

public:
	ConstantBuffer();
	~ConstantBuffer();
private:
	void CreateBuffer();
	void CreateView();
public:
	void Init(CBV_REGISTER reg, UINT32 size, UINT32 count);
	void Clear();
	void PushData(void* buffer, UINT32 size);
	
	//전역 Data 넣기
	void PushGlobalData(void* buffer, UINT32 size);

public: //Get 함수
	D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress(UINT32 index);
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(UINT32 index);
};

