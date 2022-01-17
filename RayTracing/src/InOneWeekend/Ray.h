#pragma once

#include <glm/vec3.hpp>

namespace RayTracing {

	class Ray
	{
	public:
		Ray();
		Ray(const glm::vec3& origin, const glm::vec3& direction);

		const glm::vec3& GetOrigin() const { return m_Origin; }
		const glm::vec3& GetDirection() const { return m_Direction; }

		glm::vec3 At(float t) const;
	public:
		glm::vec3 m_Origin;
		glm::vec3 m_Direction;
	};

}
