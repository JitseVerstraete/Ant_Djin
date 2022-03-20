#pragma once
#include "PeterObserver.h"
#include "PeterPepperComponent.h"
#include "Singleton.h"


class AchievementSystem : public dae::Singleton<AchievementSystem>,  public PeterObserver
{
public:

    void PlayerDied() override{}
    void GainedPoints(int totalPoints) override;
private:
    
    friend Singleton<AchievementSystem>;
    AchievementSystem();
};

