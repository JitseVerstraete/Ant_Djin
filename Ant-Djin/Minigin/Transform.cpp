#include "MiniginPCH.h"
#include "Transform.h"
#include "GameObject.h"

using namespace glm;

dae::Transform::Transform(GameObject* gameObject)
	:m_LocalPos{ 0.f, 0.f, 0.f },
	m_LocalScale{ 1.f, 1.f },
	m_LocalRot{ 0.f },
	m_pGameObject{ gameObject },
	m_positionDirty{ false },
	m_rotationDirty{ false },
	m_scaleDirty{ false }
{
	m_WorldPos = m_LocalPos;
	m_WorldRot = m_LocalRot;
	m_WorldScale = m_LocalScale;
}

const glm::vec3& dae::Transform::GetLocalPosition() const
{
	return m_LocalPos;
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	if (m_positionDirty)
	{
		//calculate new world pos
		if (m_pParent == nullptr)
		{
			m_WorldPos = m_LocalPos;
		}
		else
		{

			m_WorldPos = m_pParent->GetWorldPosition() + m_LocalPos;
		}
		m_positionDirty = false;

	}

	return m_WorldPos;
}

void dae::Transform::Translate(const glm::vec3& movement)
{
	m_LocalPos += movement;
	SetPositionDirty();
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPos = pos;
	SetPositionDirty();
}

void dae::Transform::SetWorldPosition(const glm::vec3& /*pos*/)
{
	//todo: yet to implement

}

const glm::vec2& dae::Transform::GetLocalScale() const
{
	return m_LocalScale;
}

const glm::vec2& dae::Transform::GetWorldScale()
{
	if (m_scaleDirty)
	{
		m_scaleDirty = false;
		//calculate new world pos
		if (m_pParent == nullptr)
		{
			m_WorldScale = m_LocalScale;
		}
		else
		{
			m_WorldScale = m_LocalScale * m_pParent->GetWorldScale();
		}
	}
	return m_WorldScale;
}

void dae::Transform::SetScale(const glm::vec2& scale)
{
	m_LocalScale = scale;
	SetScaleDirty();
}

float dae::Transform::GetWorldRotation()
{
	if (m_rotationDirty)
	{
		m_rotationDirty = false;
		//calculate new world pos
		if (m_pParent == nullptr)
		{
			m_WorldRot = m_LocalRot;
		}
		else
		{
			m_WorldRot = m_LocalRot + m_pParent->GetWorldRotation();
		}
	}
	return m_WorldRot;
}

float dae::Transform::GetLocalRotation() const
{
	return m_LocalRot;
}

void dae::Transform::Rotate(float deltaDegrees)
{
	m_LocalRot += deltaDegrees;
	SetRotationDirty();
}

void dae::Transform::SetLocalRotation(float degrees)
{
	m_LocalRot = degrees;
	SetRotationDirty();
}

void dae::Transform::SetWorldRotation(float /*degrees*/)
{
	//todo: yet to implement
}

void dae::Transform::SetParent(Transform* pParent, bool keepWorldTransform)
{
	//remove itself from children of previous parent
	if (m_pParent) m_pParent->RemoveChild(this);

	//set the given partent as the current parent
	m_pParent = pParent;

	//add this Transform to the list of children of new parent
	m_pParent->AddChild(this);

	//update transform   
	if (keepWorldTransform)
	{
		Translate(-m_pParent->GetWorldPosition());
	}
	else
	{
		SetPositionDirty();
	}
	
}



void dae::Transform::SetPositionDirty()
{
	m_positionDirty = true;
	for (Transform* child : m_pChildren)
	{
		if (child) child->SetPositionDirty();
	}

}

void dae::Transform::SetRotationDirty()
{
	m_rotationDirty = true;
	for (Transform* child : m_pChildren)
	{
		if (child) child->SetRotationDirty();
	}
}

void dae::Transform::SetScaleDirty()
{
	m_scaleDirty = true;
	for (Transform* child : m_pChildren)
	{
		if (child) child->SetScaleDirty();
	}
}

void dae::Transform::RemoveChild(Transform* pToRemove)
{
	//erase the given transform from the list of children
	m_pChildren.erase(pToRemove);

}

void dae::Transform::AddChild(Transform* pToAdd)
{
	m_pChildren.insert(pToAdd);
}

