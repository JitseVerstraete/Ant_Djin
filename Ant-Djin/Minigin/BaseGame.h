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

	virtual void LoadGame(){}

private:

};

