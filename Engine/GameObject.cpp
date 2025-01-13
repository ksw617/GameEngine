#include "pch.h"
#include "GameObject.h"
#include "Transform.h"

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
}


void GameObject::Awake()
{
    //��� ���۳�Ʈ�� ��ȸ�ϸ�
    for (shared_ptr<Component>& component : components)
    {
        //���۳�Ʈ�� nullptr�� �ƴϸ�
        if (component)
            component->Awake();    //Awake�Լ� ȣ��
    }
}

void GameObject::Start()
{
    //��� ���۳�Ʈ�� ��ȸ�ϸ�
    for (shared_ptr<Component>& component : components)
    {
        //���۳�Ʈ�� nullptr�� �ƴϸ�
        if (component)
            component->Start();    //Start�Լ� ȣ��
    }
}

void GameObject::Update()
{
    //��� ���۳�Ʈ�� ��ȸ�ϸ�
    for (shared_ptr<Component>& component : components)
    {
        //���۳�Ʈ�� nullptr�� �ƴϸ�
        if (component)
            component->Update();    //Update�Լ� ȣ��
    }
}

void GameObject::LateUpdate()
{
    //��� ���۳�Ʈ�� ��ȸ�ϸ�
    for (shared_ptr<Component>& component : components)
    {
        //���۳�Ʈ�� nullptr�� �ƴϸ�
        if (component)
            component->LateUpdate();    //LateUpdate�Լ� ȣ��
    }
}

shared_ptr<Transform> GameObject::GetTransform()
{
    //Transform �ε��� ����ؼ�
    UINT8 index = static_cast<UINT8>(COMPONENT_TYPE::TRANSFORM);

    //Tranform ����Ʈ �����ͷ� ����ȯ�Ͽ� ��ȯ 
    return static_pointer_cast<Transform>(components[index]);
}
