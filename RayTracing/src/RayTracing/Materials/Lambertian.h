#pragma once

#include "RayTracing/Materials/Material.h"

namespace RayTracing {

	class Lambertian : public Material
	{
	public:
		Lambertian(const glm::vec3& albedo);

		virtual bool Scatter(const Ray& inRay, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const override;
	private:
		glm::vec3 m_Albedo;
	};

}
