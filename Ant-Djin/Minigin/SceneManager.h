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
		void Destroy();

		GameScene* CreateEmptyScene(const std::string& name);
		void AddScene(GameScene* pScene);
		GameScene* GetScene(const std::string& name);
		void SetActiveScene(const std::string& sceneName);
		GameScene* GetActiveScene() { return m_pActiveScene; }


		void ProcessScene();


		void Update();
		void FixedUpdate();
		void Render();


	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<GameScene*> m_Scenes;
		GameScene* m_pActiveScene = nullptr;

		bool m_switchScene;
		std::string m_switchSceneName;
	};
}
 