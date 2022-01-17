#include <glm/geometric.hpp>

#include "InOneWeekend/Ray.h"

namespace RayTracing {

	Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
		: m_Origin(origin), m_Direction(direction)
	{
	}

	glm::vec3 Ray::GetColor() const
	{
		if (HitSphere(glm::vec3{ 0, 0, -1 }, 0.5f))
			return glm::vec3{ 1, 0, 0 };

		glm::vec3 unitDirection = glm::normalize(m_Direction);
		float t = 0.5f * (unitDirection.y + 1.0f);
		return (1.0f - t) * glm::vec3{ 1.0f, 1.0f, 1.0f } + t * glm::vec3{ 0.5f, 0.7f, 1.0f };
	}

	bool Ray::HitSphere(const glm::vec3& center, float radius) const
	{
		glm::vec3 oc = m_Origin - center;

		float a = glm::dot(m_Direction, m_Direction);
		float b = 2.0f * glm::dot(oc, m_Direction);
		float c = glm::dot(oc, oc) - radius * radius;

		float discriminant = b * b - 4 * a * c;

		return discriminant > 0;
	}

}
