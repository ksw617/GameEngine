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
    //모든 컴퍼넌트를 순회하며
    for (shared_ptr<Component>& component : components)
    {
        //컴퍼넌트가 nullptr이 아니면
        if (component)
            component->Awake();    //Awake함수 호출
    }
}

void GameObject::Start()
{
    //모든 컴퍼넌트를 순회하며
    for (shared_ptr<Component>& component : components)
    {
        //컴퍼넌트가 nullptr이 아니면
        if (component)
            component->Start();    //Start함수 호출
    }
}

void GameObject::Update()
{
    //모든 컴퍼넌트를 순회하며
    for (shared_ptr<Component>& component : components)
    {
        //컴퍼넌트가 nullptr이 아니면
        if (component)
            component->Update();    //Update함수 호출
    }
}

void GameObject::LateUpdate()
{
    //모든 컴퍼넌트를 순회하며
    for (shared_ptr<Component>& component : components)
    {
        //컴퍼넌트가 nullptr이 아니면
        if (component)
            component->LateUpdate();    //LateUpdate함수 호출
    }
}

shared_ptr<Transform> GameObject::GetTransform()
{
    //Transform 인덱스 계산해서
    UINT8 index = static_cast<UINT8>(COMPONENT_TYPE::TRANSFORM);

    //Tranform 스마트 포인터로 형변환하여 반환 
    return static_pointer_cast<Transform>(components[index]);
}
