#include "MiniginPCH.h"
#include "CollisionManager.h"
#include "ColliderComponent.h"
#include "GameObject.h"



void dae::CollisionManager::ProcessCollisions()
{
	//set current collision records as the previous one and clear the current one

	m_PreviousCollisions = std::move(m_CurrentCollisions);
	m_CurrentCollisions = std::set<CollisionRecord>();

	//compare every collider against every other one and make records of the collisions

	for (ColliderComponent* collider : m_Colliders)
	{
		for (ColliderComponent* compareWith : m_Colliders)
		{
			//if the colliders are the same, skip
			if (collider == compareWith) continue;

			CollisionRecord newRec{ collider, compareWith };
			if (std::find_if(m_CurrentCollisions.begin(), m_CurrentCollisions.end(), [&newRec](const CollisionRecord& rec) {return rec == newRec; }) != m_CurrentCollisions.end())
			{
				continue;
			}

			if (collider->Overlaps(compareWith))
			{
				m_CurrentCollisions.insert(CollisionRecord(collider, compareWith));
			}

		}
	}

	//check the currentcollisions for enter & stay events
	for (const CollisionRecord& record : m_CurrentCollisions)
	{

		bool prevOverlap{ m_PreviousCollisions.find(record) != m_PreviousCollisions.end() };


		CollisionType type{};
		if (prevOverlap) type = CollisionType::Stay;
		if (!prevOverlap) type = CollisionType::Enter;

		//call the on collision 
		GameObject* go1{ record.collider1->GetGameObject() };
		GameObject* go2{ record.collider2->GetGameObject() };

		go1->OnCollision(go2, type);
		go2->OnCollision(go1, type);
	}

	//check the prevCollisions for exit events
	for (const CollisionRecord& record : m_PreviousCollisions)
	{
		bool currOverlap{ m_CurrentCollisions.find(record) != m_CurrentCollisions.end() };

		if (currOverlap) continue;

		CollisionType type{ CollisionType::Exit };


		//call the on collision 
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

bool dae::CollisionRecord::operator<(const CollisionRecord& other) const
{

	if (*this == other) return false;


	if (collider1->GetId() != other.collider1->GetId())
	{
		return collider1->GetId() < other.collider1->GetId();
	}
	else
	{
		return collider2->GetId() < other.collider2->GetId();
	}

}