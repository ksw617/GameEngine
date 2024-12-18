#pragma once
class TableDescriptor
{
private:
	ComPtr<ID3D12DescriptorHeap> descHeap;	// 디스크립터 힙
	UINT64 handleSize = 0;					// 디스크립터 핸들 크기
	UINT64 groupSize = 0;					// 그룹당 디스크립터 수
	UINT64 groupCount = 0;					// 그룹의 수

	UINT32 currentGroupIndex = 0;			// 현재 그룹 인덱스
public:
	//descHeap Get 함수
	ComPtr<ID3D12DescriptorHeap> GetDescriptorHeap() { return descHeap; }
public:
	//디스크립트 힙 초기화
	void Init(UINT32 count);

	//index 초기화
	void Clear();

	//상수 버퍼 뷰(CBV) 설정
	void SetCBV(D3D12_CPU_DESCRIPTOR_HANDLE srcHandle, CBV_REGISTER reg);

	//주어진 레지스터에 대한 CPU 디스크립터 핸들 가져오기
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(CBV_REGISTER reg);

private:
	//주어진 인덱스에 대한 CPU 디스크립터 핸들 가져오기
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(UINT32 reg);


};

