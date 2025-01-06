#pragma once

//용도별 CONSTANT_BUFFER 타입을 정의 하는 열거형
enum class CONSTANT_BUFFER_TYPE : UINT8
{
	TRANSFORM,	// 변환 행렬을 저장하는 상수 버퍼
	MATERIAL,	// 재질 정보를 저장하는 상수 버퍼
	END,		// 상수 버퍼 타입의 끝

};

//상수 버퍼의 총 갯수를 정의
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

	D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress(UINT32 index);
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(UINT32 index);
};

