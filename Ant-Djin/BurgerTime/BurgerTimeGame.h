#pragma once
#include "BaseGame.h"
class BurgerTimeGame final : public BaseGame
{
public:
	BurgerTimeGame() = default;
	virtual ~BurgerTimeGame() = default;
	BurgerTimeGame(const BurgerTimeGame& other) = delete;
	BurgerTimeGame(const BurgerTimeGame&& other) = delete;
	BurgerTimeGame& operator=(const BurgerTimeGame& other) = delete;
	BurgerTimeGame& operator=(const BurgerTimeGame&& other) = delete;

	void LoadGame() override;

private:


};

