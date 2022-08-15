#pragma once
#include "Transform.h"
#include "Component.h"

#include <iostream>
#include <vector>
#include "GameScene.h"


namespace dae
{
	class GameObject final
	{
	public:
		void Update();
		void FixedUpdate();
		void Render() const;

		//components
		template<typename T> T* AddComponent(T* component);
		template <typename T> void RemoveComponent();
		template <typename T> T* GetComponent();

		void OnCollision(GameObject* other, CollisionType type);

		//transform manip
		Transform& GetTransform() { return m_Transform; }


		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		friend GameObject* GameScene::AddGameObject();
		GameObject(); // constructor private, you can only make game object through adding them in the scene
		Transform m_Transform;

		std::vector<Component*> m_pComponents;

	};




	template<typename T>
	inline T* GameObject::AddComponent(T* pComponent)
	{
		if (pComponent) m_pComponents.push_back(pComponent);
		pComponent->SetAttachedGameObject(this);
		return pComponent;
	}

	template<typename T> //typename T are classes that derive from Component base class
	inline T* GameObject::GetComponent()
	{

		for (Component* pComp : m_pComponents)
		{
			T* derivedComp = dynamic_cast<T*>(pComp);
			if (derivedComp != nullptr)
			{
				return derivedComp;
			}
		}

		return nullptr;
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		std::cout << "REMOVE COMPONENT NOT YET IMPLEMENTED!!!!\n";
		//todo: add the "remove component" implementation!
	}

}
