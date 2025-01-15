#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MonoBehaviour.h"

//�߰�
#include "MeshFilter.h"
#include "Camera.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
    AddComponent(make_shared<Transform>());
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
    component->SetGameObject(shared_from_this());

    UINT8 index = static_cast<UINT8>(component->GetType());
                                    
    if (index < FIXED_COMPONENT_COUNT)
    {
        components[index] = component;
    }
    else 
    {

        scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
    }
}


void GameObject::Awake()
{
    for (shared_ptr<Component>& component : components)
    {
        if (component)
            component->Awake(); 
    }

    for (shared_ptr<MonoBehaviour>& script : scripts)
    {
        script->Awake();
    }
}

void GameObject::Start()
{
    for (shared_ptr<Component>& component : components)
    {
        if (component)
            component->Start();  
    }

    for (shared_ptr<MonoBehaviour>& script : scripts)
    {
        script->Start();
    }
}

void GameObject::Update()
{
    for (shared_ptr<Component>& component : components)
    {
        if (component)
            component->Update();  
    }

    for (shared_ptr<MonoBehaviour>& script : scripts)
    {
        script->Update();
    }
}

void GameObject::LateUpdate()
{
    for (shared_ptr<Component>& component : components)
    {
        if (component)
            component->LateUpdate();  
    }

    for (shared_ptr<MonoBehaviour>& script : scripts)
    {
        script->LateUpdate();
    }
}

void GameObject::FinalUpdate()
{
    for (shared_ptr<Component>& component : components)
    {
        if (component)
            component->FinalUpdate();
    }
}

shared_ptr<Transform> GameObject::GetTransform()
{
    //Transform Ÿ���� ������Ʈ�� ������
    shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::TRANSFORM);

    //component �����͸� transform �����ͷ� ĳ�����Ͽ� ��ȯ
    return static_pointer_cast<Transform>(component);
}

shared_ptr<MeshFilter> GameObject::GetMeshFilter()
{
    //Transform Ÿ���� ������Ʈ�� ������
    shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::MESH_FILTER);

    //component �����͸� MeshFilter �����ͷ� ĳ�����Ͽ� ��ȯ
    return static_pointer_cast<MeshFilter>(component);
}

shared_ptr<Camera> GameObject::GetCamera()
{
    //Transform Ÿ���� ������Ʈ�� ������
    shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::CAMERA);

    //component �����͸� Camera �����ͷ� ĳ�����Ͽ� ��ȯ
    return static_pointer_cast<Camera>(component);
}

shared_ptr<Component> GameObject::GetFixedComponent(COMPONENT_TYPE type)
{
    //������Ʈ Ÿ���� ���� �ε����� ��ȯ
    UINT8 index = static_cast<UINT8>(type);

    //�ε����� ������ ������Ʈ�� ������ �ʰ����� �ʴ��� Ȯ��
    assert(index < FIXED_COMPONENT_COUNT);
    
    //������ �ε����� ������Ʈ�� ��ȯ
    return components[index];
}
