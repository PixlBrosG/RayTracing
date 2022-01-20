#include <glm/geometric.hpp>
#include <glm/gtx/norm.hpp>

#include "InOneWeekend/Ray.h"

#include "InOneWeekend/RTWeekend.h"

namespace RayTracing {

	Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
		: m_Origin(origin), m_Direction(direction)
	{
	}

#if 0
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
#endif

}
