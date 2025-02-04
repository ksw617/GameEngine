#include "pch.h"
#include "OcclusionCulling.h"
#include "Camera.h" // 카메라 뷰 행렬, 투영 행렬 받기 위해

void OcclusionCulling::FinalUpdate()
{
    //카메라의 뷰 행렬을 역행렬로 변환
    Matrix matViewInvert = Camera::StaticMatrixView.Invert();

    //카메라 투영 행렬을 역행렬로 변환
    Matrix matProjectionInvert = Camera::StaticMatrixProjection.Invert();

    //역행렬들을 곱하여 변환 행렬을 계산
    Matrix matInvert = matProjectionInvert * matViewInvert;

    //화면 좌표에서 월드 좌표로 변환된 8개의 코너 포인트를 계산
    vector<Vector3> worldPos =
    {
        XMVector3TransformCoord(Vector3(-1.f, 1.f, 0.f), matInvert),    //가까운 Top-Left point
        XMVector3TransformCoord(Vector3(1.f, 1.f, 0.f), matInvert),     //가까운 Top-Right point
        XMVector3TransformCoord(Vector3(1.f, -1.f, 0.f), matInvert),    //가까운 Bottom-Right point
        XMVector3TransformCoord(Vector3(-1.f, -1.f, 0.f), matInvert),   //가까운 Bottom-Left point

        XMVector3TransformCoord(Vector3(-1.f, 1.f, 1.f), matInvert),    //먼 Top-Left point
        XMVector3TransformCoord(Vector3(1.f, 1.f, 1.f), matInvert),     //먼 Top-Right point
        XMVector3TransformCoord(Vector3(1.f, -1.f, 1.f), matInvert),    //먼 Bottom-Right point
        XMVector3TransformCoord(Vector3(-1.f, -1.f, 1.f), matInvert),   //먼 Bottom-Left point

    };


    //각 평면을 3개의 포인트로 정의하여 계산
    planes[PLANE_FRONT] = XMPlaneFromPoints(worldPos[0], worldPos[1], worldPos[2]);  //앞쪽 평면(시계방향)
    planes[PLANE_BACK]  = XMPlaneFromPoints(worldPos[4], worldPos[7], worldPos[5]);  //뒤쪽 평면(반시계방향)
    planes[PLANE_UP]    = XMPlaneFromPoints(worldPos[4], worldPos[5], worldPos[1]);  //위쪽 평면(시계방향)
    planes[PLANE_DOWN]  = XMPlaneFromPoints(worldPos[7], worldPos[3], worldPos[6]);  //아래쪽 평면(반시계방향)
    planes[PLANE_LEFT]  = XMPlaneFromPoints(worldPos[4], worldPos[0], worldPos[7]);  //왼쪽 평면(시계방향)
    planes[PLANE_RIGHT] = XMPlaneFromPoints(worldPos[5], worldPos[6], worldPos[1]);  //오른쪽 평면(반시계방향)
}

bool OcclusionCulling::ContainSphere(const Vector3& pos, float radius)
{                                      
    //구체가 공간안에 포함하거나 걸쳐 있는치 체크
    for (const Vector4& plane : planes)
    {
        //평면의 normal 벡터 추출
        Vector3 normal = Vector3(plane.x, plane.y, plane.z);

        //평면 방정식(ax + by + cz + d)과 반지름을 사용하여 구체가 평면을 벗어났는지 확인
        if (normal.Dot(pos) + plane.w > radius)
            return false; // 벗어 났다면 false로 반환

    }

    //모든 평면을 통과하면 true로 반환
    return true;
}
