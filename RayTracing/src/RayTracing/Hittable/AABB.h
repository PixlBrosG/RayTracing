#pragma once

#include "RayTracing/Utils/RTUtils.h"

#include "RayTracing/Ray.h"

// Axis-aligned bounding rectangular parallelepiped

namespace RayTracing {

	class AABB
	{
	public:
		AABB() = default;
		AABB(const glm::vec3& a, const glm::vec3& b);

		const glm::vec3& GetMin() const { return m_Minimum; }
		const glm::vec3& GetMax() const { return m_Maximum; }

		bool IsHit(const Ray& ray, float minT, float maxT) const;
	private:
		glm::vec3 m_Minimum, m_Maximum;
	};

}
