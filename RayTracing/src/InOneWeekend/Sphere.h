#pragma once

#include <glm/vec3.hpp>

#include "InOneWeekend/Hittable.h"

namespace RayTracing {

	class Sphere : public Hittable
	{
	public:
		Sphere() = default;
		Sphere(const glm::vec3& center, float radius);

		virtual bool IsHit(const Ray& ray, float minT, float maxT, HitRecord& hitRecord) const override;

	private:
		glm::vec3 m_Center;
		float m_Radius;
	};

}
