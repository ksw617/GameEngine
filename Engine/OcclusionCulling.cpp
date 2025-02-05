#include "pch.h"
#include "OcclusionCulling.h"
#include "Camera.h" // ī�޶� �� ���, ���� ��� �ޱ� ����

void OcclusionCulling::FinalUpdate()
{
    //ī�޶��� �� ����� ����ķ� ��ȯ
    Matrix matViewInvert = Camera::StaticMatrixView.Invert();

    //ī�޶� ���� ����� ����ķ� ��ȯ
    Matrix matProjectionInvert = Camera::StaticMatrixProjection.Invert();

    //����ĵ��� ���Ͽ� ��ȯ ����� ���
    Matrix matInvert = matProjectionInvert * matViewInvert;

    //ȭ�� ��ǥ���� ���� ��ǥ�� ��ȯ�� 8���� �ڳ� ����Ʈ�� ���
    vector<Vector3> worldPos =
    {
        XMVector3TransformCoord(Vector3(-1.f, 1.f, 0.f), matInvert),    //����� Top-Left point
        XMVector3TransformCoord(Vector3(1.f, 1.f, 0.f), matInvert),     //����� Top-Right point
        XMVector3TransformCoord(Vector3(1.f, -1.f, 0.f), matInvert),    //����� Bottom-Right point
        XMVector3TransformCoord(Vector3(-1.f, -1.f, 0.f), matInvert),   //����� Bottom-Left point

        XMVector3TransformCoord(Vector3(-1.f, 1.f, 1.f), matInvert),    //�� Top-Left point
        XMVector3TransformCoord(Vector3(1.f, 1.f, 1.f), matInvert),     //�� Top-Right point
        XMVector3TransformCoord(Vector3(1.f, -1.f, 1.f), matInvert),    //�� Bottom-Right point
        XMVector3TransformCoord(Vector3(-1.f, -1.f, 1.f), matInvert),   //�� Bottom-Left point

    };


    //�� ����� 3���� ����Ʈ�� �����Ͽ� ���
    planes[PLANE_FRONT] = XMPlaneFromPoints(worldPos[0], worldPos[1], worldPos[2]);  //���� ���(�ð����)
    planes[PLANE_BACK]  = XMPlaneFromPoints(worldPos[4], worldPos[7], worldPos[5]);  //���� ���(�ݽð����)
    planes[PLANE_UP]    = XMPlaneFromPoints(worldPos[4], worldPos[5], worldPos[1]);  //���� ���(�ð����)
    planes[PLANE_DOWN]  = XMPlaneFromPoints(worldPos[7], worldPos[3], worldPos[6]);  //�Ʒ��� ���(�ݽð����)
    planes[PLANE_LEFT]  = XMPlaneFromPoints(worldPos[4], worldPos[0], worldPos[7]);  //���� ���(�ð����)
    planes[PLANE_RIGHT] = XMPlaneFromPoints(worldPos[5], worldPos[6], worldPos[1]);  //������ ���(�ݽð����)
}

bool OcclusionCulling::ContainSphere(const Vector3& pos, float radius)
{                                      
    //��ü�� �����ȿ� �����ϰų� ���� �ִ�ġ üũ
    for (const Vector4& plane : planes)
    {
        //����� normal ���� ����
        Vector3 normal = Vector3(plane.x, plane.y, plane.z);

        //��� ������(ax + by + cz + d)�� �������� ����Ͽ� ��ü�� ����� ������� Ȯ��
        if (normal.Dot(pos) + plane.w > radius)
            return false; // ���� ���ٸ� false�� ��ȯ

    }

    //��� ����� ����ϸ� true�� ��ȯ
    return true;
}
