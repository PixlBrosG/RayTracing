#include "InOneWeekend/Ray.h"

namespace RayTracing {

	Ray::Ray()
	{
	}

	Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
		: m_Origin(origin), m_Direction(direction)
	{
	}

	glm::vec3 Ray::At(float t) const
	{
		return m_Origin + t * m_Direction;
	}

}
