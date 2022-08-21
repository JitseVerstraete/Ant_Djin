#pragma once
#include "SceneManager.h"


namespace dae
{
	class GameObject;
	class CollisionManager;
	class GameScene
	{
	public:
		explicit GameScene(const std::string& name);
		GameObject* AddGameObject();
		void RemoveGameObject(GameObject* object);


		const std::string& GetName() { return m_Name; }
		
		CollisionManager* GetCollisionManager() { return m_CollisionManager; }


		void ProcessAddQueue();
		void RemoveDeletedObjects();

		virtual ~GameScene();
		GameScene(const GameScene& other) = delete;
		GameScene(GameScene&& other) = delete;
		GameScene& operator=(const GameScene& other) = delete;
		GameScene& operator=(GameScene&& other) = delete;

	protected:
		friend SceneManager;

		virtual void Initialize();
		virtual void SceneUpdate(){}

		void Update();
		void FixedUpdate();
		void Render() const;


		std::string m_Name;
		std::vector <GameObject*> m_Objects;

		std::vector<GameObject*> m_AddQueue;
		

		CollisionManager* m_CollisionManager;
	};
}