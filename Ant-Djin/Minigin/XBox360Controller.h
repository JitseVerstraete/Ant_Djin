#pragma once


namespace dae
{
	enum class ControllerButton
	{
		DpadLeft,
		DpadRight,
		DpadUp,
		DpadDown,
		Start,
		Back,
		LThumb,
		RThumb,
		LShoulder,
		RShoulder,
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	class XBox360Controller
	{
	public:
		XBox360Controller(int index);
		~XBox360Controller();
		void ProcessInput();

		bool IsDown(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;
		bool IsReleased(ControllerButton button) const;

	private:
		class XBox360ControllerImpl;
		XBox360ControllerImpl* m_pImpl;
	};

}
