#pragma once
#include "Singleton.h"
#include <vector>
#include <iostream>




namespace dae
{
	class GameObject;
	class ColliderComponent;
	struct CollisionRecord
	{
		ColliderComponent* collider1;
		ColliderComponent* collider2;

		bool overlap;

		bool operator==(const CollisionRecord& other)
		{
			return (collider1 == other.collider1 && collider2 == other.collider2) || (collider1 == other.collider2 && collider2 == other.collider1);
		}
	};

	enum class CollisionType
	{
		Enter,
		Stay,
		Exit
	};

	class Shape
	{
	public:
		Shape(int left, int top, int width, int height, GameObject* object);


		bool Overlaps(const Shape& other);

		int GetWorldLeft()const;
		int GetWorldTop()const;
		int GetWidth()const;
		int GetHeight()const;


	private:

		int m_Left;
		int m_Top;
		int m_Width;
		int m_Height;

		GameObject* m_LinkedObject;
		bool ValInRange(int val, int min, int max)
		{
			return val >= min && val <= max;
		}
	};


	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void ProcessCollisions();
		void AddCollider(ColliderComponent* collider);
		void RemoveCollider(ColliderComponent* collider);


	private:
		CollisionManager() = default;
		friend Singleton<CollisionManager>;

		std::vector<ColliderComponent*> m_Colliders;

		std::vector<CollisionRecord> m_CurrentCollisions;
		std::vector<CollisionRecord> m_PreviousCollisions;

	};


}