#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
		friend Scene* SceneManager::CreateScene(const std::string& name);
	public:
		void Add(GameObject*  pObject);

		void Update();
		void FixedUpdate();
		void Render() const;

		const std::string& GetName() { return m_Name; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		explicit Scene(const std::string& name);


		std::string m_Name;
		std::vector <GameObject*> m_Objects{};

	};

}