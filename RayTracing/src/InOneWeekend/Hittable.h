#pragma once

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "InOneWeekend/Ray.h"

namespace RayTracing {

	struct HitRecord
	{
		glm::vec3 Point;
		glm::vec3 Normal;
		float T;
		bool FrontFace;

		void SetFaceNormal(const Ray& ray, const glm::vec3& outwardNormal)
		{
			FrontFace = glm::dot(ray.GetDirection(), outwardNormal) < 0;
			Normal = FrontFace ? outwardNormal : -outwardNormal;
		}
	};

	class Hittable
	{
	public:
		virtual bool IsHit(const Ray& ray, float minT, float maxT, HitRecord& hitRecord) const = 0;
	};

}
