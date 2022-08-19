#pragma once
#include "CollisionManager.h"

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* pGo);
		virtual ~Component() = default;

		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void Render() const {}
		virtual void OnCollision(GameObject*, CollisionType) {}

		GameObject* GetGameObject() const;
		void SetAttachedGameObject(GameObject* go);

	protected:

		GameObject* m_pAttachedGameObject = nullptr; //No ownership on this pointer
	};

}
