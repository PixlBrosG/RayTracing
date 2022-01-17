#include <glm/geometric.hpp>
#include <glm/gtx/norm.hpp>

#include "InOneWeekend/Ray.h"

namespace RayTracing {

	Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
		: m_Origin(origin), m_Direction(direction)
	{
	}

	glm::vec3 Ray::GetColor() const
	{
		float t = HitSphere(glm::vec3{ 0, 0, -1 }, 0.5f);

		if (t > 0.0f)
		{
			glm::vec3 N = glm::normalize(At(t) - glm::vec3{ 0, 0, -1 });
			return 0.5f * glm::vec3{ N.r + 1, N.g + 1, N.b + 1 };
		}

		glm::vec3 unitDirection = glm::normalize(m_Direction);
		t = 0.5f * (unitDirection.y + 1.0f);
		return (1.0f - t) * glm::vec3{ 1.0f, 1.0f, 1.0f } + t * glm::vec3{ 0.5f, 0.7f, 1.0f };
	}

	float Ray::HitSphere(const glm::vec3& center, float radius) const
	{
		glm::vec3 oc = m_Origin - center;

		// dot(P,P) = squared length of P
		float a = glm::length2(m_Direction);
		float halfB = glm::dot(oc, m_Direction);
		float c = glm::length2(oc) - radius * radius;

		float discriminant = halfB * halfB - a * c;

		if (discriminant < 0)
			return -1.0f;
		else
			return (-halfB - glm::sqrt(discriminant)) / a;
	}

}
