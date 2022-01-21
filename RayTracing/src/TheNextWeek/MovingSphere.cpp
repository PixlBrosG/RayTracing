#include "TheNextWeek/MovingSphere.h"

namespace RayTracing {

	MovingSphere::MovingSphere(const glm::vec3& center0, const glm::vec3& center1, float time0, float time1, float radius, Ref<Material> materialPtr)
		: m_Center0(center0), m_Center1(center1), m_Time0(time0), m_Time1(time1), m_Radius(radius), m_MaterialPtr(materialPtr)
	{
	}

	bool MovingSphere::IsHit(const Ray& ray, float minT, float maxT, HitRecord& hitRecord) const
	{
		glm::vec3 center = GetCenter(ray.GetTime());
		glm::vec3 oc = ray.GetOrigin() - center;

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
		glm::vec3 outwardNormal = (hitRecord.Point - center) / m_Radius;
		hitRecord.SetFaceNormal(ray, outwardNormal);
		hitRecord.MaterialPtr = m_MaterialPtr;

		return true;
	}

	glm::vec3 MovingSphere::GetCenter(float time) const
	{
		return m_Center0 + ((time - m_Time0) / (m_Time1 - m_Time0)) * (m_Center1 - m_Center0);
	}

}
