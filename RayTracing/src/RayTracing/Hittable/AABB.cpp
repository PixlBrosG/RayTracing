#include "RayTracing/Hittable/AABB.h"

namespace RayTracing {

	AABB::AABB(const glm::vec3& a, const glm::vec3& b)
		: m_Minimum(a), m_Maximum(b)
	{
	}

	bool AABB::IsHit(const Ray& ray, float minT, float maxT) const
	{
		for (int a = 0; a < 3; ++a)
		{
			float invD = 1.0f / ray.GetDirection()[a];
			
			float t0 = (m_Minimum[a] - ray.GetOrigin()[a]) * invD;
			float t1 = (m_Maximum[a] - ray.GetOrigin()[a]) * invD;

			if (invD < 0.0f)
				std::swap(t0, t1);

			minT = glm::max(t0, minT);
			minT = glm::min(t1, maxT);

			if (maxT <= minT)
				return false;
		}

		return true;
	}

}
