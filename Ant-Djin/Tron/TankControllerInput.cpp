#include "TankControllerInput.h"
#include "TankComponent.h"
#include "InputManager.h"

using namespace dae;


void TankControllerInput::AddBinding(KeyboardButtonInfo button, TankAction action)
{
	m_KeyboardBindings.emplace_back(std::pair<KeyboardButtonInfo, TankAction>(button, action));
}

void TankControllerInput::AddBinding(dae::ControllerButtonInfo button, TankAction action)
{
	m_ControllerBindings.emplace_back(std::pair<ControllerButtonInfo, TankAction>(button, action));
}

void TankControllerInput::ProcessControlls()
{

	for (auto pair : m_KeyboardBindings)
	{
		if(dae::InputManager::GetInstance().IsPressed(pair.first.button, pair.first.mode)) ProcessAction(pair.second);
	}

	for (auto pair : m_ControllerBindings)
	{
		if (dae::InputManager::GetInstance().IsPressed(pair.first.button, pair.first.mode, pair.first.controllerIndex)) ProcessAction(pair.second);
	}
}

void TankControllerInput::ProcessAction(TankAction action)
{
	switch (action)
	{
	case TankAction::MoveLeft:
		m_pTankComponent->AddMovementInput({ -1, 0 });
		break;
	case TankAction::MoveRight:
		m_pTankComponent->AddMovementInput({ 1, 0 });
		break;
	case TankAction::MoveUp:
		m_pTankComponent->AddMovementInput({ 0, 1 });
		break;
	case TankAction::MoveDown:
		m_pTankComponent->AddMovementInput({ 0, -1 });
		break;
	case TankAction::AimClockwise:
		m_pTankComponent->AddGunRotation(1);
		break;
	case TankAction::AimCounterClockwise:
		m_pTankComponent->AddGunRotation(-1);
		break;
	case TankAction::Shoot:
		m_pTankComponent->Shoot();
		break;
	default:
		break;
	}
}
