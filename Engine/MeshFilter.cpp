#include "pch.h"
#include "MeshFilter.h"
#include "Mesh.h"
#include "Material.h"

void MeshFilter::Render()
{
	//Material Update �Լ� ȣ��
	material->Update();

	//Mesh ����
	mesh->Render();

}
