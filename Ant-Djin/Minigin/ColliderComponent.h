#pragma once
#include "Component.h"
#include "Shapes.h"

namespace dae
{

	class GameObject;
	class ColliderComponent final : public dae::Component
	{
	public:
		ColliderComponent(dae::GameObject* pGo, const Shape& shape);
		~ColliderComponent();

		const Shape& GetShape() const { return m_Shape; };

		bool Overlaps(const ColliderComponent* other) const;
		unsigned int GetId() { return m_Id; }

		void Update() override;
		void Render() const override;
		void OnCollision(GameObject* other, CollisionType type) override;

	private:
		Shape m_Shape;
		
		bool overlapped{};

		unsigned int m_Id;
		static unsigned int m_ColliderCounter;

	};

}
