#pragma once
#include "Transform.h"
#include "Component.h"

#include <iostream>
#include <vector>


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


		//hirearchy
		void AddChild(GameObject* childObject) { m_pChildren.push_back(childObject); }
		std::vector<GameObject*> Getchildren() const { return m_pChildren; }
		GameObject* GetParent() const { return m_pParent; }


		//transform manip
		Transform& GetTransform() { return m_Transform; }


		GameObject(GameObject* pParent = nullptr);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;

		std::vector<Component*> m_pComponents;

		//scenegraph structure
		std::vector<GameObject*> m_pChildren;
		GameObject* m_pParent;


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
