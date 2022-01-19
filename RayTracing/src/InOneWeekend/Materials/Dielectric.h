#pragma once

#include "InOneWeekend/Materials/Material.h"

namespace RayTracing {

	class Dielectric : public Material
	{
	public:
		Dielectric(float indexOfRefraction);

		virtual bool Scatter(const Ray& inRay, const HitRecord& hitRecord, glm::vec3& attenuation, Ray& scattered) const override;
	private:
		float m_IndexOfRefraction;
	};

}
