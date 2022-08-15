#pragma once
#include "Component.h"
#include "CollisionManager.h"

namespace dae
{


	class GameObject;
	class ColliderComponent : public dae::Component
	{
	public:
		ColliderComponent(dae::GameObject* pGo, const Shape& shape);
		~ColliderComponent();

		const Shape& GetShape() { return m_Shape; };

	private:
		Shape m_Shape;

	};

}
