#include "RayTracing/Materials/Dielectric.h"

namespace RayTracing {

	Dielectric::Dielectric(float indexOfRefraction)
		: m_IndexOfRefraction(indexOfRefraction)
	{
	}

	bool Dielectric::Scatter(const Ray& inRay, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const
	{
		attenuation = glm::vec3(1);
		float refractionRatio = hitRecord.FrontFace ? (1.0f / m_IndexOfRefraction) : m_IndexOfRefraction;

		glm::vec3 unitDirection = glm::normalize(inRay.GetDirection());
		
		float cosTheta = glm::min(glm::dot(-unitDirection, hitRecord.Normal), 1.0f);
		float sinTheta = sqrt(1.0f - cosTheta * cosTheta);

		bool cannotRefract = refractionRatio * sinTheta > 1.0f;
		glm::vec3 direction;

		if (cannotRefract || Reflectance(cosTheta, refractionRatio) > Utils::RandomFloat())
			direction = Utils::Reflect(unitDirection, hitRecord.Normal);
		else
			direction = Utils::Refract(unitDirection, hitRecord.Normal, refractionRatio);

		scattered = Ray(hitRecord.Point, direction, inRay.GetTime());
		return true;
	}

	float Dielectric::Reflectance(float cosine, float refIdx)
	{
		// Use Schlick's approximation for reflectance
		float r0 = (1 - refIdx) / (1 + refIdx);
		r0 *= r0;
		return r0 + (1 - r0) * (float)glm::pow(1 - cosine, 5);
	}

}
