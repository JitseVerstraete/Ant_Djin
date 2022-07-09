#pragma once
#include "Component.h"

namespace dae
{

	class MoveComponent : public dae::Component
	{
		class GameObject;

	public:
		MoveComponent(dae::GameObject* object) : Component(object) {}
		virtual void Update() override;
		virtual void Render() const override {}
		virtual void FixedUpdate() override {}

	private:
		const float m_MoveSpeed = 100.f;
		int m_moveDir = -1;

		const float m_RotSpeed = 45.f;
		
	};

}
