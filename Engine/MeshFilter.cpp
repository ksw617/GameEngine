#include "pch.h"
#include "MeshFilter.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h" // �߰�

void MeshFilter::Render()
{
	//�ش� Transform�� PushData ����
	GetTransfrom()->PushData();

	material->Update();
	mesh->Render();

}
