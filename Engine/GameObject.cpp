#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MonoBehaviour.h"

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
    //모든 컴포넌트를 순회하며 FinalUpdate 함수 호출
    for (shared_ptr<Component>& component : components)
    {
        if (component)
            component->FinalUpdate();
    }
}

shared_ptr<Transform> GameObject::GetTransform()
{
    UINT8 index = static_cast<UINT8>(COMPONENT_TYPE::TRANSFORM);

    return static_pointer_cast<Transform>(components[index]);
}
