#pragma once
#include "Singleton.h"
#include <memory>
#include <string>
#include <vector>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* CreateScene(const std::string& name);
		Scene* GetScene(std::string name);
		void SetActiveScene(Scene* pScene);

		void Update();
		void FixedUpdate();
		void Render();


	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<Scene*> m_Scenes;
		Scene* m_pActiveScene = nullptr;
	};
}
