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

	for (ColliderComponent* collider : m_Colliders)
	{
		for (ColliderComponent* compareWith : m_Colliders)
		{
			//if the colliders are the same, skip
			if (collider == compareWith) continue;


			CollisionRecord newRecord{ CollisionRecord(collider, compareWith) };
			//if the record of these colliders already exists, skip
			if (std::find_if(m_CurrentCollisions.begin(), m_CurrentCollisions.end(), [&newRecord](const CollisionRecord& record) {return record == newRecord; }) != m_CurrentCollisions.end())
			{
				continue;
			}

			//check if the colliders overlap and store the record in m_currentCollisions

			if (collider->Overlaps(compareWith))
			{
				newRecord.overlap = true;
			}

			m_CurrentCollisions.push_back(newRecord);
		}
	}

	//call the OnCollision function of all colliding game objects
	for (const CollisionRecord& record : m_CurrentCollisions)
	{
		bool currOverlap{};
		bool prevOverlap{};

		currOverlap = record.overlap;

		auto it = std::find(m_PreviousCollisions.begin(), m_PreviousCollisions.end(), record);
		if (it == m_PreviousCollisions.end()) prevOverlap = false;
		else
		{
			prevOverlap = it->overlap;
		}

		if (!currOverlap && !prevOverlap) continue;

		CollisionType type{};
		if (currOverlap && prevOverlap) type = CollisionType::Stay;
		if (currOverlap && !prevOverlap) type = CollisionType::Enter;
		if (!currOverlap && prevOverlap) type = CollisionType::Exit;

		GameObject* go1{ record.collider1->GetGameObject() };
		GameObject* go2{ record.collider2->GetGameObject() };

		go1->OnCollision(go2, type);
		go2->OnCollision(go1, type);
	}

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

