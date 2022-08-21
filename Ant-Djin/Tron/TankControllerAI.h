#pragma once
#include "TankControllerBase.h"

class TankControllerAI final : public TankControllerBase
{
public:
	TankControllerAI() = default;
	~TankControllerAI() = default;


	void ProcessControlls() override;

private:
	//data required to make movement/shoot decisions

};

