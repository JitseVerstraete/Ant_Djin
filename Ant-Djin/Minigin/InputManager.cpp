#include "MiniginPCH.h"
#include "InputManager.h"
#include "SDL.h"


dae::InputManager::InputManager()
{
	for (int i{}; i < 4; i++)
	{
		m_Controllers.insert({ i, new XBox360Controller(i) });
	}

	memset(m_PreviousKeyboardState, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
	memcpy(m_CurrentKeyboardState, SDL_GetKeyboardState(nullptr), sizeof(Uint8) * SDL_NUM_SCANCODES);


	m_PreviousMouseState = 0;
	m_CurrentMouseState = SDL_GetMouseState(&m_CurrentMousePos.x, &m_CurrentMousePos.y);

	m_PrevMousePos = m_CurrentMousePos;

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


	memcpy(m_PreviousKeyboardState, m_CurrentKeyboardState, sizeof(Uint8) * SDL_NUM_SCANCODES);
	memcpy(m_CurrentKeyboardState, SDL_GetKeyboardState(nullptr), sizeof(Uint8) * SDL_NUM_SCANCODES);

	m_PrevMousePos = m_CurrentMousePos;
	m_PreviousMouseState = m_CurrentMouseState;
	m_CurrentMouseState = SDL_GetMouseState(&m_CurrentMousePos.x, &m_CurrentMousePos.y);

	m_DeltaMousePos = m_CurrentMousePos - m_PrevMousePos;

	SDL_Event e{};
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
			break;
		default:
			break;
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
	case dae::ButtonMode::HeldDown:
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

bool dae::InputManager::IsPressed(SDL_Scancode button, ButtonMode mode)
{
	bool currentButton{};
	bool prevButton{};
	currentButton = m_CurrentKeyboardState[button];
	prevButton = m_PreviousKeyboardState[button];


	switch (mode)
	{
	case dae::ButtonMode::HeldDown:
		return currentButton && prevButton;
		break;
	case dae::ButtonMode::Pressed:
		return currentButton && !prevButton;
		break;
	case dae::ButtonMode::Released:
		return !currentButton && prevButton;
		break;
	default:
		break;
	}


	return false;
}

bool dae::InputManager::IsPressed(MouseButton button, ButtonMode mode)
{
	bool currentButton{};
	bool prevButton{};
	currentButton = m_CurrentMouseState & SDL_BUTTON(static_cast<int>(button));
	prevButton = m_PreviousMouseState & SDL_BUTTON(static_cast<int>(button));

	switch (mode)
	{
	case dae::ButtonMode::HeldDown:
		return currentButton && prevButton;
		break;
	case dae::ButtonMode::Pressed:
		return currentButton && !prevButton;
		break;
	case dae::ButtonMode::Released:
		return !currentButton && prevButton;
		break;
	default:
		break;
	}
	
	return false;
}