#include "MiniginPCH.h"
#include "InputManager.h"
#include "SDL.h"


dae::InputManager::InputManager()
{
	for (int i{}; i < 4; i++)
	{
		m_Controllers.insert({ i, new XBox360Controller(i) });
	}
}

dae::InputManager::~InputManager()
{
	for (auto mapping : m_consoleCommands)
	{
		delete mapping;
	}

	for (auto pair : m_Controllers)
	{
		delete pair.second;
	}
}

void dae::InputManager::AddCommand(ControllerButtonCommand* buttonCommand)
{
	m_consoleCommands.push_back(buttonCommand);
}

bool dae::InputManager::ProcessInput()
{
	for (auto& controller : m_Controllers)
	{
		controller.second->ProcessInput();
	}

	SDL_Event e{};
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
	}


	return true;

}

void dae::InputManager::Update()
{
	for (auto commandAction : m_consoleCommands)
	{
		if (IsPressed(commandAction->button, commandAction->mode, commandAction->controllerIndex))
		{
			commandAction->pCommand->Execute();
		}
	}
}

bool dae::InputManager::IsPressed(ControllerButton button, ButtonMode bMode, int controllerIndex) const
{
	switch (bMode)
	{
	case dae::ButtonMode::Down:
		return m_Controllers.at(controllerIndex)->IsDown(button);
		break;

	case dae::ButtonMode::Pressed:
		return m_Controllers.at(controllerIndex)->IsPressed(button);
		break;

	case dae::ButtonMode::Released:
		return m_Controllers.at(controllerIndex)->IsReleased(button);
		break;

	default:
		return false;
		break;
	}
}
