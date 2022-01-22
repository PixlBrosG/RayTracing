#include "RayTracing/Hittable/Sphere.h"

#include <glm/geometric.hpp>
#include <glm/gtx/norm.hpp>

namespace RayTracing {

	Sphere::Sphere(const glm::vec3& center, float radius, Ref<Material> materialPtr)
		: m_Center(center), m_Radius(radius), m_MaterialPtr(materialPtr)
	{
	}

	bool Sphere::IsHit(const Ray& ray, float minT, float maxT, HitRecord& hitRecord) const
	{
		glm::vec3 oc = ray.GetOrigin() - m_Center;

		float a = glm::length2(ray.GetDirection());
		float halfB = glm::dot(oc, ray.GetDirection());
		float c = glm::length2(oc) - m_Radius * m_Radius;

		float discriminant = halfB * halfB - a * c;

		if (discriminant < 0)
			return false;

		float sqrtd = glm::sqrt(discriminant);

		// Find the nearest root that lies in the acceptable range
		float root = (-halfB - sqrtd) / a;
		if (root < minT || maxT < root)
		{
			root = (-halfB + sqrtd) / a;
			if (root < minT || maxT < root)
				return false;
		}

		hitRecord.T = root;
		hitRecord.Point = ray.At(hitRecord.T);
		glm::vec3 outwardNormal = (hitRecord.Point - m_Center) / m_Radius;
		hitRecord.SetFaceNormal(ray, outwardNormal);
		hitRecord.MaterialPtr = m_MaterialPtr;

		return true;
	}

	bool Sphere::BoundingBox(float time0, float time1, AABB& outputBox) const
	{
		outputBox = AABB(m_Center - glm::vec3(m_Radius), m_Center + glm::vec3(m_Radius));
		return true;
	}

}
