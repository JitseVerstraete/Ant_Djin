#pragma once

#pragma warning(push)
#pragma warning(disable:4201)    
#include<glm/glm.hpp>
#pragma warning (pop)

#include <set>

namespace dae
{
	class GameObject;
		

	class Transform final
	{
	public:
		Transform(GameObject* gameObject);

		//position functions
		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetWorldPosition();

		void Translate(const glm::vec3& movement);
		void SetLocalPosition(const glm::vec3& pos);
		void SetWorldPosition(const glm::vec3& pos);

		//scale functions
		const glm::vec2& GetLocalScale() const;
		const glm::vec2& GetWorldScale();

		void SetScale(const glm::vec2& scale);
		
		//rotation functions
		float GetWorldRotation() ;
		float GetLocalRotation() const;

		void Rotate(float deltaDegrees);
		void SetLocalRotation(float degrees);
		void SetWorldRotation(float degrees);


		//hierarchy functions (add child)
		void SetParent(Transform* pParent, bool keepWorldTransform = true); //sets parent, removes itself as child from previous parent, set as child for new parent & update transform
		const std::set<Transform*>& GetChildren() { return m_pChildren; }

		GameObject* GetGameObject() { return m_pGameObject; }

	private:
		glm::vec3 m_LocalPos;
		glm::vec2 m_LocalScale;
		float m_LocalRot;

		bool m_positionDirty = false;
		bool m_rotationDirty = false;
		bool m_scaleDirty = false;

		glm::vec3 m_WorldPos;
		glm::vec2 m_WorldScale;
		float m_WorldRot;


		//game object to which this transform belongs
		GameObject* m_pGameObject; 



		//parent-child stuff
		Transform* m_pParent;
		std::set<Transform*> m_pChildren;
	


		void SetPositionDirty();
		void SetRotationDirty();
		void SetScaleDirty();

		//hierarchy helpers
		void RemoveChild(Transform* pToRemove); 
		void AddChild(Transform* pToAdd);

	};

}

