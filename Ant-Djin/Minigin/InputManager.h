#pragma once

#include <vector>
#include <map>
#include "Command.h"
#include "XBox360Controller.h"
#include "Singleton.h"


namespace dae
{

	enum class ButtonMode
	{
		HeldDown,
		Pressed,
		Released
	};

	enum class MouseButton
	{
		Left = 1,
		Middle = 2,
		Right = 3,
		Thumb1 = 4,
		Thumb2 = 5
	};

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
		bool IsPressed(ControllerButton button, ButtonMode mode, int controllerIndex) const;
		bool IsPressed(SDL_Scancode button, ButtonMode mode);
		bool IsPressed(MouseButton button, ButtonMode mode);
		glm::ivec2 GetMousePos() { return m_CurrentMousePos; }
		glm::ivec2 GetMouseMovement() { return m_DeltaMousePos; }


	private:
		friend class Singleton<InputManager>;
		InputManager();



		std::vector<ControllerButtonCommand*> m_consoleCommands{};
		std::map<int, XBox360Controller*> m_Controllers{};

		//keyboard stuff
		Uint8 m_CurrentKeyboardState[SDL_NUM_SCANCODES];
		Uint8 m_PreviousKeyboardState[SDL_NUM_SCANCODES];

		//mouse stuff
		//mouse position
		glm::ivec2 m_PrevMousePos{};
		glm::ivec2 m_CurrentMousePos{};
		glm::ivec2 m_DeltaMousePos{};

		//mouse keys
		Uint32 m_CurrentMouseState;
		Uint32 m_PreviousMouseState;

	};
}