#pragma once
class ConstantBuffer
{
private:
	//상수 버퍼 리소스
	ComPtr<ID3D12Resource> cbvBuffer;
	//매핑된 버퍼 데이터 포인터
	BYTE* mappedBuffer = nullptr;
	//각 요소의 크기
	int elementSize = 0;
	//요소의 갯수
	int elementCount = 0;
	//현재 인덱스
	int currentIndex = 0;
public:
	ConstantBuffer();
	~ConstantBuffer();
private:
	//상수 버퍼 생성
	void CreateBuffer();
public:
	//상수 버퍼 초기화
	void Init(int size, int count);
	//상수 버퍼 데이터 초기화
	void Clear();
	//상수 버퍼에 데이터 푸시
	void PushData(int rootParamIndex, void* buffer, int size);

	//GPU 가상 주소 가져오기
	D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress(int index);
};

