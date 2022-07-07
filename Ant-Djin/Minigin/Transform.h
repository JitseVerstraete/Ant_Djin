#pragma once

#pragma warning(push)
#pragma warning(disable:4201)   
#include<glm/glm.hpp>
#pragma warning (pop)

#include <vector>

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
		const glm::vec2& GetWorldScale() const;

		void SetScale(const glm::vec2& scale);
		
		//rotation functions
		float GetWorldRotation() const;
		float GetLocalRotation() const;

		void Rotate(float deltaDegrees);
		void SetLocalRotation(float degrees);
		void SetWorldRotation(float degrees);


		//hierarchy functions (add child, remove child...)


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
		std::vector<Transform*> m_pChildren;


		void SetPositionDirty();
		void SetRotationDirty();
		void SetScaleDirty();

	};
}
