#include "MiniginPCH.h"
#include "XBox360Controller.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#pragma comment (lib, "xinput.lib")

#include <iostream>

using namespace dae;

class XBox360Controller::XBox360ControllerImpl
{
public:
	XBox360ControllerImpl(int controllerIndex) : m_ControllerIndex{ DWORD(controllerIndex) } {}

	void ProcessInput();

	bool IsDown(unsigned int button) const;
	bool IsPressed(unsigned int button) const;
	bool IsReleased(unsigned int button) const;

private:
	DWORD m_ControllerIndex{};


	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PrevState{};
	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};
};



XBox360Controller::XBox360Controller(int index)
{
	m_pImpl = new XBox360ControllerImpl(index);
}

dae::XBox360Controller::~XBox360Controller()
{
	delete m_pImpl;
}

void XBox360Controller::ProcessInput()
{
	m_pImpl->ProcessInput();
}

bool XBox360Controller::IsDown(ControllerButton button) const
{

	switch (button)
	{
	case dae::ControllerButton::DpadLeft:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_DPAD_LEFT);
		break;
	case dae::ControllerButton::DpadRight:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_DPAD_RIGHT);
		break;
	case dae::ControllerButton::DpadUp:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_DPAD_UP);
		break;
	case dae::ControllerButton::DpadDown:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_DPAD_DOWN);
		break;
	case dae::ControllerButton::Start:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_START);
		break;
	case dae::ControllerButton::Back:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_BACK);
		break;
	case dae::ControllerButton::LThumb:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_LEFT_THUMB);
		break;
	case dae::ControllerButton::RThumb:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_RIGHT_THUMB);
		break;
	case dae::ControllerButton::LShoulder:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_LEFT_SHOULDER);
		break;
	case dae::ControllerButton::RShoulder:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_RIGHT_SHOULDER);
		break;
	case dae::ControllerButton::ButtonA:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_A);
		break;
	case dae::ControllerButton::ButtonB:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_B);
		break;
	case dae::ControllerButton::ButtonX:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_X);
		break;
	case dae::ControllerButton::ButtonY:
		return m_pImpl->IsDown(XINPUT_GAMEPAD_Y);
		break;
	default:
		break;
	}
	return false;
}

bool XBox360Controller::IsPressed(ControllerButton button) const
{

	switch (button)
	{
	case dae::ControllerButton::DpadLeft:
		return m_pImpl->IsPressed(XINPUT_GAMEPAD_DPAD_LEFT);
		break;
	case dae::ControllerButton::DpadRight:
		return m_pImpl->IsPressed(XINPUT_GAMEPAD_DPAD_RIGHT);
		break;
	case dae::ControllerButton::DpadUp:
		return m_pImpl->IsPressed(VK_GAMEPAD_DPAD_UP);
		break;
	case dae::ControllerButton::DpadDown:
		return m_pImpl->IsPressed(VK_GAMEPAD_DPAD_DOWN);
		break;
	case dae::ControllerButton::Start:
		return m_pImpl->IsPressed(XINPUT_GAMEPAD_START);
		break;
	case dae::ControllerButton::Back:
		return m_pImpl->IsPressed(XINPUT_GAMEPAD_BACK);
		break;
	case dae::ControllerButton::LThumb:
		return m_pImpl->IsPressed(XINPUT_GAMEPAD_LEFT_THUMB);
		break;
	case dae::ControllerButton::RThumb:
		return m_pImpl->IsPressed(XINPUT_GAMEPAD_RIGHT_THUMB);
		break;
	case dae::ControllerButton::LShoulder:
		return m_pImpl->IsPressed(XINPUT_GAMEPAD_LEFT_SHOULDER);
		break;
	case dae::ControllerButton::RShoulder:
		return m_pImpl->IsPressed(XINPUT_GAMEPAD_RIGHT_SHOULDER);
		break;
	case dae::ControllerButton::ButtonA:
		return m_pImpl->IsPressed(XINPUT_GAMEPAD_A);
		break;
	case dae::ControllerButton::ButtonB:
		return m_pImpl->IsPressed(XINPUT_GAMEPAD_B);
		break;
	case dae::ControllerButton::ButtonX:
		return m_pImpl->IsPressed(XINPUT_GAMEPAD_X);
		break;
	case dae::ControllerButton::ButtonY:
		return m_pImpl->IsPressed(XINPUT_GAMEPAD_Y);
		break;
	default:
		break;
	}
	return false;
}

bool XBox360Controller::IsReleased(ControllerButton button) const
{
	switch (button)
	{
	case dae::ControllerButton::DpadLeft:
		return m_pImpl->IsReleased(XINPUT_GAMEPAD_DPAD_LEFT);
		break;
	case dae::ControllerButton::DpadRight:
		return m_pImpl->IsReleased(XINPUT_GAMEPAD_DPAD_RIGHT);
		break;
	case dae::ControllerButton::DpadUp:
		return m_pImpl->IsReleased(VK_GAMEPAD_DPAD_UP);
		break;
	case dae::ControllerButton::DpadDown:
		return m_pImpl->IsReleased(VK_GAMEPAD_DPAD_DOWN);
		break;
	case dae::ControllerButton::Start:
		return m_pImpl->IsReleased(XINPUT_GAMEPAD_START);
		break;
	case dae::ControllerButton::Back:
		return m_pImpl->IsReleased(XINPUT_GAMEPAD_BACK);
		break;
	case dae::ControllerButton::LThumb:
		return m_pImpl->IsReleased(XINPUT_GAMEPAD_LEFT_THUMB);
		break;
	case dae::ControllerButton::RThumb:
		return m_pImpl->IsReleased(XINPUT_GAMEPAD_RIGHT_THUMB);
		break;
	case dae::ControllerButton::LShoulder:
		return m_pImpl->IsReleased(XINPUT_GAMEPAD_LEFT_SHOULDER);
		break;
	case dae::ControllerButton::RShoulder:
		return m_pImpl->IsReleased(XINPUT_GAMEPAD_RIGHT_SHOULDER);
		break;
	case dae::ControllerButton::ButtonA:
		return m_pImpl->IsReleased(XINPUT_GAMEPAD_A);
		break;
	case dae::ControllerButton::ButtonB:
		return m_pImpl->IsReleased(XINPUT_GAMEPAD_B);
		break;
	case dae::ControllerButton::ButtonX:
		return m_pImpl->IsReleased(XINPUT_GAMEPAD_X);
		break;
	case dae::ControllerButton::ButtonY:
		return m_pImpl->IsReleased(XINPUT_GAMEPAD_Y);
		break;
	default:
		break;
	}
	return false;
}



void XBox360Controller::XBox360ControllerImpl::ProcessInput()
{
	CopyMemory(&m_PrevState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	


	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PrevState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool XBox360Controller::XBox360ControllerImpl::IsDown(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}

bool XBox360Controller::XBox360ControllerImpl::IsPressed(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}

bool XBox360Controller::XBox360ControllerImpl::IsReleased(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;
}

