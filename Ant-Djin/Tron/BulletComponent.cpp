#include "BulletComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "GameTime.h"


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
	GetGameObject()->GetTransform().Translate({ m_Velocity.x * elapsed, m_Velocity.y * elapsed, 0 });
}
