#pragma once
#include "CollisionManager.h"

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* pGo) :m_pAttachedGameObject{ pGo } {};
		virtual ~Component() {};

		virtual void Update() {};
		virtual void FixedUpdate(){};
		virtual void Render() const{};
		virtual void OnCollision(GameObject* , CollisionType ){}

		void SetAttachedGameObject(GameObject* pGO);
		GameObject* GetGameObject() const;

	protected:
		GameObject* m_pAttachedGameObject = nullptr; //No ownership on this pointer
	};

}
