#pragma once
#include "Transform.h"
#include "Component.h"


namespace dae
{

	class GameObject final
	{
	public:
		void Update();
		void FixedUpdate();
		void Render() const;

		//components
		template<typename T>
		T* AddComponent();

		template <typename T>
		void RemoveComponent();

		template <typename T>
		T* GetComponent();


		//transform manip
		void SetPosition(float x, float y);
		Transform GetTransform() const { return m_Transform; }


		GameObject() = default;
		virtual ~GameObject(); 
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;

		std::vector<Component*> m_pComponents;

	};




	template<typename T>
	inline T* GameObject::AddComponent()
	{
		T* newComp = new T();
		m_pComponents.push_back(newComp);
		newComp->SetAttachedGameObject(this);
		return newComp;
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
