#pragma once

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* pGo) :m_pAttachedGameObject{ pGo } {};
		virtual ~Component() {};

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;

		void SetAttachedGameObject(GameObject* pGO);
		GameObject* GetGameObject() const;

	private:
		GameObject* m_pAttachedGameObject = nullptr; //No ownership on this pointer
	};

}
