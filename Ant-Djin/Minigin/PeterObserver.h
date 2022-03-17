#pragma once

class PeterObserver
{
public:
	PeterObserver() = default;
	virtual ~PeterObserver() = default;
	virtual void PlayerDied() = 0;
	virtual void GainedPoints() = 0;
};