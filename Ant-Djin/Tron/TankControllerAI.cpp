#include "TankControllerAI.h"
#include "TankComponent.h"

void TankControllerAI::ProcessControlls()
{

	//choose what direction to move in, and wether or not to shoot 
	auto tanks = TankComponent::GetPlayerTanks();

	auto pos = m_pTankComponent->GetGameObject()->GetTransform().GetWorldPosition();
	float distance{ FLT_MAX };
	TankComponent* closestTank = nullptr;
	for (auto tank : tanks)
	{
		auto otherPos = tank->GetGameObject()->GetTransform().GetWorldPosition();
		float newDistance = float( pow(pos.x - otherPos.x, 2) + pow(pos.y - otherPos.y, 2));
		if (newDistance < distance)
		{
			closestTank = tank;
			distance = newDistance;
		}
	}

	if (closestTank == nullptr) return;

	//movement
	glm::vec3 tankPos = closestTank->GetGameObject()->GetTransform().GetWorldPosition();
	glm::vec3 thisPos = m_pTankComponent->GetGameObject()->GetTransform().GetWorldPosition();


	glm::ivec2 moveInput{};

	auto xDif = abs(tankPos.x - thisPos.x);
	auto yDif = abs(tankPos.y - thisPos.y);

	if (xDif > yDif)
	{
		moveInput.x = tankPos.x < thisPos.x ? -1 : 1;

	}
	else
	{
		moveInput.y = tankPos.y < thisPos.y ? 1 : -1;
	}

	m_pTankComponent->AddMovementInput(moveInput);


	//shooting
	switch (m_pTankComponent->GetMovementDir())
	{
	case Direction::North:
		if (xDif < 5.f && tankPos.y < thisPos.y) m_pTankComponent->Shoot();
		break;
	case Direction::South:
		if (xDif < 5.f && tankPos.y > thisPos.y) m_pTankComponent->Shoot();
		break;
	case Direction::East:
		if (yDif < 5.f && tankPos.x > thisPos.x) m_pTankComponent->Shoot();
		break;
	case Direction::West:
		if (yDif < 5.f && tankPos.x < thisPos.x) m_pTankComponent->Shoot();
		break;
	default:
		break;
	}


}
