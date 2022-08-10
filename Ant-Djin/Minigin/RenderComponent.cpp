#include "MiniginPCH.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(GameObject* pGo, glm::fvec2 offset)
	:Component(pGo)
	, m_Offset{ offset }
{
}

void dae::RenderComponent::Update()
{
	//no update needed for this component
}

void dae::RenderComponent::FixedUpdate()
{
	//no fixed update implementation for this component
}

void dae::RenderComponent::Render() const
{
	auto pos = GetGameObject()->GetTransform().GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, GetGameObject()->GetTransform(), m_Offset);
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}
 
void dae::RenderComponent::SetTexture(Texture2D* tex)
{
	m_pTexture = tex;
}
