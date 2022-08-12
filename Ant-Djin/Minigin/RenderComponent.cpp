#include "MiniginPCH.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(GameObject* pGo, glm::fvec2 offset)
	:Component(pGo)
	, m_Offset{ offset }
	, m_SourceRect{}

{
}



dae::RenderComponent::~RenderComponent()
{
	if (m_SourceRect) delete m_SourceRect;
	if (m_DestRect) delete m_DestRect;
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


	Renderer::GetInstance().RenderTexture(*m_pTexture, GetGameObject()->GetTransform(), m_SourceRect, m_Offset);


}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(Texture2D* tex)
{
	m_pTexture = tex;
}

void dae::RenderComponent::SetSourceRect(const SDL_Rect& source)
{
	if (!m_SourceRect)
	{
		m_SourceRect = new SDL_Rect{ source };
	}
	else
	{
		(*m_SourceRect) = source;
	}
}

void dae::RenderComponent::SetDestRect(const SDL_FRect& dest)
{
	if (!m_DestRect)
	{
		m_DestRect = new SDL_FRect{ dest };
	}
	else
	{
		(*m_DestRect) = dest;
	}
}
