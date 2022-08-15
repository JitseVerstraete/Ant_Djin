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

dae::Shape::Shape(int left, int top, int width, int height, GameObject* object)
	:m_Left{ left }, m_Top{ top }, m_Width{ width }, m_Height{ height }, m_LinkedObject{ object }
{}

bool dae::Shape::Overlaps(const Shape& other)
{
	

	bool xAligned{ ValInRange(GetWorldLeft(), other.GetWorldLeft(), other.GetWorldLeft() + other.m_Width)
				|| ValInRange(other.GetWorldLeft(), GetWorldLeft(), GetWorldLeft() + m_Width) };

	bool yAligned{ ValInRange(GetWorldTop(), other.GetWorldTop(), other.GetWorldTop() + other.m_Height)
				|| ValInRange(other.GetWorldTop(), GetWorldTop(), GetWorldTop() + m_Height) };

	return xAligned && yAligned;
}

int dae::Shape::GetWorldLeft() const
{
	return  m_Left + (int)m_LinkedObject->GetTransform().GetWorldPosition().x;
}

int dae::Shape::GetWorldTop() const
{
	return m_Top + (int)m_LinkedObject->GetTransform().GetWorldPosition().y;
}

int dae::Shape::GetWidth() const 
{
	return m_Width;
}

int dae::Shape::GetHeight() const
{
	return m_Height;
}
