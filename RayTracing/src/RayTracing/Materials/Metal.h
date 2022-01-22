#pragma once

#include "RayTracing/Materials/Material.h"

namespace RayTracing {

	class Metal : public Material
	{
	public:
		Metal(const glm::vec3& albedo, float fuzz);

		virtual bool Scatter(const Ray& inRay, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const override;
	private:
		glm::vec3 m_Albedo;
		float m_Fuzz;
	};

}
