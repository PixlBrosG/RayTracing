#pragma once

#include <glm/vec3.hpp>

#include "RayTracing/Hittable/Hittable.h"

namespace RayTracing {

	class Sphere : public Hittable
	{
	public:
		Sphere() = default;
		Sphere(const glm::vec3& center, float radius, Ref<Material> materialPtr);

		virtual bool IsHit(const Ray& ray, float minT, float maxT, HitRecord& hitRecord) const override;
		virtual bool BoundingBox(float time0, float time1, AABB& outputBox) const override;
	private:
		glm::vec3 m_Center;
		float m_Radius;
		Ref<Material> m_MaterialPtr;
	};

}
