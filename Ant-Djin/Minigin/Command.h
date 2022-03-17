#pragma once
#include "GameObject.h"
namespace dae
{
	class Command
	{
	public:
		Command(GameObject* pGo) :m_pGameObject{ pGo } {};
		virtual ~Command() = default;
		virtual void Execute() = 0;
	protected:
		GameObject* GetGameObject() { return m_pGameObject; }
	private:
		GameObject* m_pGameObject = nullptr;
	};

}
