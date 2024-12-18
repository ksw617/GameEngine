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
};

