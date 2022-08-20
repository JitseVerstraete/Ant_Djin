#pragma once
#include "TankComponent.h"



class TankControllerBase
{
public:
	TankControllerBase() = default;
	virtual ~TankControllerBase() = default;

	virtual void ProcessControlls() = 0;
	virtual void SetTankComponent(TankComponent* tankComp) { m_pTankComponent = tankComp; }


protected:	
	TankComponent* m_pTankComponent;

};

