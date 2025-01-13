#include "pch.h"
#include "MeshFilter.h"
#include "Mesh.h"
#include "Material.h"

void MeshFilter::Render()
{
	//Material Update 함수 호출
	material->Update();

	//Mesh 랜더
	mesh->Render();

}
