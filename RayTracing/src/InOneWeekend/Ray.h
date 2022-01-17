#pragma once

#include <glm/vec3.hpp>

namespace RayTracing {

	class Ray
	{
	public:
		Ray() = default;
		Ray(const glm::vec3& origin, const glm::vec3& direction);

		const glm::vec3& GetOrigin() const { return m_Origin; }
		const glm::vec3& GetDirection() const { return m_Direction; }

		glm::vec3 At(float t) const { return m_Origin + t * m_Direction; }
		glm::vec3 GetColor() const;

		bool HitSphere(const glm::vec3& center, float radius) const;
	public:
		glm::vec3 m_Origin;
		glm::vec3 m_Direction;
	};

}
