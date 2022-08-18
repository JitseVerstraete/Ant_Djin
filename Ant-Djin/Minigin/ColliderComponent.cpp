#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "Renderer.h"

using namespace dae;
unsigned int ColliderComponent::m_ColliderCounter = 0;

ColliderComponent::ColliderComponent(dae::GameObject* pGo, const Shape& shape) : Component(pGo), m_Shape{ shape }
{
	GetGameObject()->GetScene()->GetCollisionManager()->AddCollider(this);
	m_Id = m_ColliderCounter++;
}

ColliderComponent::~ColliderComponent()
{
	GetGameObject()->GetScene()->GetCollisionManager()->RemoveCollider(this);
}

bool dae::ColliderComponent::Overlaps(const ColliderComponent* other) const
{
	auto posThis{ GetGameObject()->GetTransform().GetWorldPosition() };
	auto posOther{ other->GetGameObject()->GetTransform().GetWorldPosition() };
	return ShapesOverlapping(m_Shape, glm::vec2{ posThis.x, posThis.y }, other->GetShape(), glm::vec2{ posOther.x, posOther.y });
}

void dae::ColliderComponent::Update()
{

}

void dae::ColliderComponent::Render() const
{
	glm::ivec2 worldPos{ GetGameObject()->GetTransform().GetWorldPosition().x + m_Shape.left,
					GetGameObject()->GetTransform().GetWorldPosition().y + m_Shape.top };


	if (overlapped)
	{
		Renderer::GetInstance().DrawRectangle({ worldPos.x, worldPos.y }, { m_Shape.width, m_Shape.height }, { 0, 255, 0, 255 }, false);
	}
	else
	{
		Renderer::GetInstance().DrawRectangle({ worldPos.x, worldPos.y }, { m_Shape.width, m_Shape.height }, { 255, 0, 0, 255 }, false);
	}
}

void dae::ColliderComponent::OnCollision(GameObject* , CollisionType type)
{
	switch (type)
	{
	case dae::CollisionType::Enter:
		overlapped = true;
		break;
	case dae::CollisionType::Stay:
		break;
	case dae::CollisionType::Exit:
		overlapped = false;
		break;
	default:
		break;
	}
}
