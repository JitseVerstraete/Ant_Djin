#pragma once
#include "Component.h"
#include "Shapes.h"

namespace dae
{


	class GameObject;
	class ColliderComponent : public dae::Component
	{
	public:
		ColliderComponent(dae::GameObject* pGo, const Shape& shape);
		~ColliderComponent();

		const Shape& GetShape() { return m_Shape; };

		bool Overlaps(ColliderComponent& other);

		void Update() override;
		void Render() const override;
		void OnCollision(GameObject* other, CollisionType type) override;

	private:
		Shape m_Shape;
		
		bool overlapped{};


	};

}
