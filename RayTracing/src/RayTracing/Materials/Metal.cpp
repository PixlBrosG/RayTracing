#include "RayTracing/Materials/Metal.h"

namespace RayTracing {

	Metal::Metal(const glm::vec3& albedo, float fuzz)
		: m_Albedo(albedo), m_Fuzz(fuzz < 1 ? fuzz : 1)
	{
	}

	bool Metal::Scatter(const Ray& inRay, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const
	{
		glm::vec3 reflected = Utils::Reflect(glm::normalize(inRay.GetDirection()), hitRecord.Normal);
		scattered = Ray(hitRecord.Point, reflected + m_Fuzz * Utils::RandomInUnitSphere(), inRay.GetTime());
		attenuation = m_Albedo;
		return glm::dot(scattered.GetDirection(), hitRecord.Normal) > 0;
	}

}
