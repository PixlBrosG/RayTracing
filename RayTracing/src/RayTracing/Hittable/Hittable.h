#pragma once

#include "RayTracing/Core/Base.h"

#include "RayTracing/Utils/RTUtils.h"

#include "RayTracing/Hittable/AABB.h"

namespace RayTracing {

	class Material;

	struct HitRecord
	{
		glm::vec3 Point;
		glm::vec3 Normal;
		Ref<Material> MaterialPtr;
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
		virtual bool BoundingBox(float time0, float time1, AABB& outputBox) const = 0;
	};

}
