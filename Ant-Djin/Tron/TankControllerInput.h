#pragma once
#include "TankControllerBase.h"
#include "InputManager.h"
#include <vector>
#include <utility>

enum class TankAction
{
	MoveLeft,
	MoveRight,
	MoveUp,
	MoveDown,
	AimClockwise,
	AimCounterClockwise,
	Shoot
};




class TankControllerInput final : public TankControllerBase
{
public:
	TankControllerInput() = default;
	~TankControllerInput() = default;

	//Add Binding
	void AddBinding(dae::KeyboardButtonInfo button, TankAction action);
	void AddBinding(dae::ControllerButtonInfo button, TankAction action);

	void ProcessControlls() override;

private:

	std::vector<std::pair<dae::KeyboardButtonInfo, TankAction>> m_KeyboardBindings;
	std::vector<std::pair<dae::ControllerButtonInfo, TankAction>> m_ControllerBindings;

	void ProcessAction(TankAction action);

};

