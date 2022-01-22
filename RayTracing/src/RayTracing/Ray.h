#pragma once

#include <glm/vec3.hpp>

namespace RayTracing {

	class Ray
	{
	public:
		Ray() = default;
		Ray(const glm::vec3& origin, const glm::vec3& direction, float time = 0.0f);

		const glm::vec3& GetOrigin() const { return m_Origin; }
		const glm::vec3& GetDirection() const { return m_Direction; }
		float GetTime() const { return m_Time; }

		glm::vec3 At(float t) const { return m_Origin + t * m_Direction; }
	public:
		glm::vec3 m_Origin;
		glm::vec3 m_Direction;
		float m_Time;
	};

}
