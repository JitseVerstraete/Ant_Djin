#include "BulletComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "GameTime.h"
#include "GameObject.h"
#include "Shapes.h"
#include "ColliderComponent.h"

using namespace dae;

BulletComponent::BulletComponent(dae::GameObject* pGo, dae::RenderComponent* render, const glm::vec3& pos, const glm::vec2& vel)
	: Component(pGo)
	, m_Velocity{ vel }
{
	render->SetTexture(ResourceManager::GetInstance().LoadTexture("Bullet.png"));
	GetGameObject()->GetTransform().SetLocalPosition(pos);
}

void BulletComponent::Update()
{
	float elapsed{ GameTime::GetInstance().GetElapsed() };
	GetGameObject()->GetTransform().Translate({ m_Velocity.x * elapsed, m_Velocity.y * elapsed, 0 }
	);

	m_BouncedThisFrame = false;
}


void BulletComponent::OnCollision(dae::GameObject* other, CollisionType type)
{
	
	if (type == CollisionType::Enter)
	
	{
		if (other->m_Tag == "wall")
		{
			if (m_BouncedThisFrame) return;
			//check what side of the collider the bullet hit, and bounce the bullet to the coorect direction
			auto collider{ other->GetComponent<ColliderComponent>() };
			if (collider)
			{
				Shape colShape = collider->GetShape();
				colShape.left += (int)other->GetTransform().GetWorldPosition().x;
				colShape.top += (int)other->GetTransform().GetWorldPosition().y;

				glm::vec3 ballPos{ GetGameObject()->GetTransform().GetWorldPosition() };
				auto ballColl = GetGameObject()->GetComponent<ColliderComponent>();
				if (!ballColl) return;
				int ballrad{ ballColl->GetShape().width / 2 };

				float xProximity{};
				if (m_Velocity.x > 0)
				{
					xProximity = abs(colShape.left - (ballPos.x + ballrad));
				}
				else
				{
					xProximity = abs((colShape.left + colShape.width) - (ballPos.x - ballrad));

				}

				float yProximity{};
				if (m_Velocity.y > 0)
				{
					yProximity = abs(colShape.top - (ballPos.y + ballrad));
				}
				else
				{
					yProximity = abs((colShape.top + colShape.height) - (ballPos.y - ballrad));

				}


				if (xProximity < yProximity) m_Velocity.x = -m_Velocity.x;
				if (xProximity >= yProximity) m_Velocity.y = -m_Velocity.y;

				m_BouncedThisFrame = true;
			}
		}
	}
}
