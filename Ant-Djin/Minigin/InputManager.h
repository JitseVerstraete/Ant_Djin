#pragma once

#include <vector>
#include <map>
#include "Command.h"
#include "XBox360Controller.h"
#include "Singleton.h"


namespace dae
{

	struct ControllerButtonCommand
	{
		ControllerButtonCommand(int index, ControllerButton button, ButtonMode mode, Command* command) :controllerIndex{ index }, button{ button }, mode{ mode }, pCommand{ command } {}
		~ControllerButtonCommand() { delete pCommand; }

		int controllerIndex{};
		ControllerButton button{};
		ButtonMode mode{};
		Command* pCommand = nullptr; //owner of the command pointer
	};


	class InputManager final : public Singleton<InputManager>
	{


	public:
		~InputManager();

		void AddCommand(ControllerButtonCommand* buttonCommand);
		bool ProcessInput();
		void Update();
		bool IsPressed(ControllerButton button, ButtonMode bMode, int controllerIndex) const;

	private:
		friend class Singleton<InputManager>;
		InputManager();
		std::vector<ControllerButtonCommand*> m_consoleCommands{};
		std::map<int, XBox360Controller*> m_Controllers{};
	};
}