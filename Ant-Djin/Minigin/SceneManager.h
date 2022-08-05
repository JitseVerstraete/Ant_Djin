#pragma once
#include "Singleton.h"
#include <memory>
#include <string>
#include <vector>

namespace dae
{
	class GameScene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		GameScene* CreateEmptyScene(const std::string& name);
		void AddScene(GameScene* pScene);
		GameScene* GetScene(std::string name);
		void SetActiveScene(GameScene* pScene);

		void Update();
		void FixedUpdate();
		void Render();


	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<GameScene*> m_Scenes;
		GameScene* m_pActiveScene = nullptr;
	};
}
