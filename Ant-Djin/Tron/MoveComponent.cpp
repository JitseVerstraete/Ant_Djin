#include "MoveComponent.h"

#include "GameTime.h"
#include "GameObject.h"


using namespace glm;

void dae::MoveComponent::Update()
{ 
	vec3 pos = m_pAttachedGameObject->GetTransform().GetWorldPosition();

	if (pos.x < 100 && m_moveDir < 0)
	{
		m_moveDir = 1;
	}

	if (pos.x > 300 && m_moveDir > 0)
	{
		m_moveDir = -1;
	}

	float movement = m_moveDir * m_MoveSpeed * GameTime::GetInstance().GetElapsed();
	m_pAttachedGameObject->GetTransform().Translate( vec3{movement, 0.f, 0.f});
	m_pAttachedGameObject->GetTransform().Rotate(GameTime::GetInstance().GetElapsed() * m_RotSpeed);

}
