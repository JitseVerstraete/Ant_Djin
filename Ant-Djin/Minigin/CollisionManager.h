#pragma once
#include "Singleton.h"
#include <vector>
#include <set>
#include <iostream>




namespace dae
{
	class GameObject;
	class ColliderComponent;
	struct CollisionRecord
	{
		CollisionRecord(ColliderComponent* comp1, ColliderComponent* comp2) :collider1{ comp1 }, collider2{ comp2 }{}

		ColliderComponent* collider1;
		ColliderComponent* collider2;


		bool operator==(const CollisionRecord& other) const
		{
			return (collider1 == other.collider1 && collider2 == other.collider2) || (collider1 == other.collider2 && collider2 == other.collider1);
		}

		bool Contains(ColliderComponent* comp) const { return collider1 == comp || collider2 == comp; }

		//when given one of the two components in the record, return the other one
		ColliderComponent* GetOtherCollider(ColliderComponent* collider) 
		{
			if (collider == collider1) return collider2;
			if (collider == collider2) return collider1;
			return nullptr;
		}

		bool operator<(const CollisionRecord& other) const;


	};

	enum class CollisionType
	{
		Enter,
		Stay,
		Exit
	};


	class CollisionManager final
	{
	public:
		void ProcessCollisions();
		void AddCollider(ColliderComponent* collider);
		void RemoveCollider(ColliderComponent* collider);

		void CallExitEvent(GameObject* go);


	private:
		friend class GameScene;
		CollisionManager() = default;
		CollisionManager(const CollisionManager& other) = delete;
		CollisionManager(const CollisionManager&& other) = delete;

		std::vector<ColliderComponent*> m_Colliders;

		std::set<CollisionRecord> m_CurrentCollisions;
		std::set<CollisionRecord> m_PreviousCollisions;

		

	};


}