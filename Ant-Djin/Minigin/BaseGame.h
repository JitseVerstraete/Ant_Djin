#pragma once

class BaseGame
{
public:
	BaseGame() = default;
	virtual ~BaseGame() = default;
	BaseGame(const BaseGame& other) = delete;
	BaseGame(const BaseGame&& other) = delete;
	BaseGame& operator=(const BaseGame& other) = delete;
	BaseGame& operator=(const BaseGame&& other) = delete;

	void SetWindowDimensions(int w, int h)
	{
		m_WindowWidth = w;
		m_WindowHeight = h;
	}

	virtual void LoadGame(){}

protected:
	int m_WindowWidth{};
	int m_WindowHeight{};

private:

};

