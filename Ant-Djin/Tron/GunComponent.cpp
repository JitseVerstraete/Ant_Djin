#include "GunComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "GameTime.h"
#include "RenderComponent.h"
#include "InputManager.h"



using namespace dae;

GunComponent::GunComponent(GameObject* pGo, dae::RenderComponent* render) : Component(pGo)
{
	render->SetTexture(ResourceManager::GetInstance().LoadTexture("RedGun.png"));
}

void GunComponent::Update()
{
	int rotationInput{};
	if (InputManager::GetInstance().IsPressed(SDL_Scancode::SDL_SCANCODE_COMMA, ButtonMode::HeldDown)) rotationInput -= 1;
	if (InputManager::GetInstance().IsPressed(SDL_Scancode::SDL_SCANCODE_PERIOD, ButtonMode::HeldDown)) rotationInput += 1;
	if (InputManager::GetInstance().IsPressed(SDL_Scancode::SDL_SCANCODE_RALT, ButtonMode::Pressed)) std::cout << "FIRE\n";


	//handle shooting logic
	GetGameObject()->GetTransform().Rotate(GameTime::GetInstance().GetElapsed() * m_RotationSpeed * rotationInput);


}
