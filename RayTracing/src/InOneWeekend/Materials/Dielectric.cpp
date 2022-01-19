#include "InOneWeekend/Materials/Dielectric.h"

namespace RayTracing {

	Dielectric::Dielectric(float indexOfRefraction)
		: m_IndexOfRefraction(indexOfRefraction)
	{
	}

	bool Dielectric::Scatter(const Ray& inRay, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const
	{
		attenuation = glm::vec3{ 1, 1, 1 };

		float refractionRatio = hitRecord.FrontFace ? (1.0f / m_IndexOfRefraction) : m_IndexOfRefraction;

		glm::vec3 unitDirection = glm::normalize(inRay.GetDirection());
		glm::vec3 refracted = Utils::Refract(unitDirection, hitRecord.Normal, refractionRatio);

		scattered = Ray(hitRecord.Point, refracted);
		return true;
	}

}
