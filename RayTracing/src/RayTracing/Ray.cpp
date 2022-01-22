#include <glm/geometric.hpp>
#include <glm/gtx/norm.hpp>

#include "RayTracing/Ray.h"

#include "RayTracing/Utils/RTUtils.h"

namespace RayTracing {

	Ray::Ray(const glm::vec3& origin, const glm::vec3& direction, float time)
		: m_Origin(origin), m_Direction(direction), m_Time(time)
	{
	}

}
