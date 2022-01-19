#pragma once

#include "InOneWeekend/RTWeekend.h"
#include "InOneWeekend/Hittable.h"

namespace RayTracing {

	class Material
	{
	public:
		virtual bool Scatter(const Ray& inRay, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const = 0;
	};
}
