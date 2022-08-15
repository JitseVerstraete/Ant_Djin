#include "MiniginPCH.h"
#include "CollisionManager.h"
#include "ColliderComponent.h"
#include "GameObject.h"

void dae::CollisionManager::ProcessCollisions()
{
	//set current collision records as the previous one and clear the current one

	m_PreviousCollisions = std::move(m_CurrentCollisions);
	m_CurrentCollisions = std::vector<CollisionRecord>();

	//compare every collider against every other one and make records of the collisions
	
	std::cout << "number of colliders: " << m_Colliders.size() << std::endl;

	//call the OnCollision function of every colliding game objects

}

void dae::CollisionManager::AddCollider(dae::ColliderComponent* collider)
{
	auto it = std::find(m_Colliders.begin(), m_Colliders.end(), collider);
	if (it == m_Colliders.end())
	{
		//add collider to the list
		m_Colliders.push_back(collider);
	}
}

void dae::CollisionManager::RemoveCollider(dae::ColliderComponent* collider)
{

	//remove collider from the list
	m_Colliders.erase(std::remove(m_Colliders.begin(), m_Colliders.end(), collider), m_Colliders.end());

}

