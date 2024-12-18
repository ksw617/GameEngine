#include "pch.h"
#include "TableDescriptor.h"
#include "GameEngine.h" // 호출

void TableDescriptor::Init(UINT32 count)
{
	//그룹수 결정
	groupCount = count;

	//디스크립터 힙 디스크립트 설정
	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = count * REGISTER_COUNT; // 전체 디스크립트 수
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // 쉐이더에서 힙이 보이도록 설정
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; // 힙타입을 CBV/SRV/UAV로 설정

	//디스크립터 힙 생성
	GameEngine::Get().GetDevice()->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&descHeap));
	
	//디스크립터 핸들 크기 가져오기
	handleSize = GameEngine::Get().GetDevice()->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//그룹 크기 계산(디스크립터 핸들 크기 * 레지스터 갯수)
	groupSize = handleSize * REGISTER_COUNT;
}

void TableDescriptor::Clear()
{
	//현재 그룹 인덱스를 0으로 초기화 하여 디스크립터 힙을 초기 상태로 재설정
	currentGroupIndex = 0;
}

void TableDescriptor::SetCBV(D3D12_CPU_DESCRIPTOR_HANDLE srcHandle, CBV_REGISTER reg)
{
	//주어진 레지스터에 대한 CPU 디스크립터 핸들을 가져옴
	D3D12_CPU_DESCRIPTOR_HANDLE descHandle = GetCPUHandle(reg);

	UINT32 descRange = 1;	//대상 범위는 1개의 디스크립터
	UINT32 srcRange = 1;	//소스 범위도 1개의 디스크립터

	GameEngine::Get().GetDevice()->GetDevice()->CopyDescriptors
	(
		1, &descHandle, &descRange, // 대상 디스크립터
		1, &srcHandle, &srcRange,	// 소스 디스크립터
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV // 디스크립터 힙 타입
	);
}

D3D12_CPU_DESCRIPTOR_HANDLE TableDescriptor::GetCPUHandle(CBV_REGISTER reg)
{
	//CBV_REGISTER 열거형을 UIN32로 변환하여 오버로드된 GetCPUHandle을 호출
	return GetCPUHandle(static_cast<UINT32>(reg));
}

D3D12_CPU_DESCRIPTOR_HANDLE TableDescriptor::GetCPUHandle(UINT32 reg)
{
	//디스크립터 힙의 시작 CPU 디스크립터 핸들 가져옴
	D3D12_CPU_DESCRIPTOR_HANDLE handle = descHeap->GetCPUDescriptorHandleForHeapStart();

	//현재 그룹 인덱스를 기준으로 핸들을 오프셋
	handle.ptr += currentGroupIndex * groupSize;
	handle.ptr += reg * handleSize;

	return handle;
}
