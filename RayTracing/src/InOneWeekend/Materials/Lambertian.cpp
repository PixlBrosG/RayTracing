#include "InOneWeekend/Materials/Lambertian.h"

namespace RayTracing {

	Lambertian::Lambertian(const glm::vec3& albedo)
		: m_Albedo(albedo)
	{
	}

	bool Lambertian::Scatter(const Ray& inRay, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const
	{
		glm::vec3 scatterDirection = hitRecord.Normal + Utils::RandomUnitVector();
		
		// Catch degenerate scatter direction
		if (Utils::IsNearZero(scatterDirection))
			scatterDirection = hitRecord.Normal;

		scattered = Ray(hitRecord.Point, scatterDirection);
		attenuation = m_Albedo;
		return true;
	}
}
