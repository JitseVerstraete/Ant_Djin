#pragma once
#include "BaseGame.h"
class TronGame final : public BaseGame
{
public:
	TronGame() = default;
	virtual ~TronGame() = default;
	TronGame(const TronGame& other) = delete;
	TronGame(const TronGame&& other) = delete;
	TronGame& operator=(const TronGame& other) = delete;
	TronGame& operator=(const TronGame&& other) = delete;

	void LoadGame() override;

private:


};

