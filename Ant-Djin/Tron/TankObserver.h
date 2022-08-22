#pragma once

#include "TankComponent.h"

class TankObserver
{
public:
	virtual void EnemyKilled(TankType type, TankType killedBy) = 0;
};

