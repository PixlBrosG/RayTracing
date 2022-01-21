#pragma once

#include "Common/RTUtils.h"
#include "Common/Hittable.h"

namespace RayTracing {

	class MovingSphere : public Hittable
	{
	public:
		MovingSphere() = default;
		MovingSphere(const glm::vec3& center0, const glm::vec3& center1, float time0, float time1, float radius, Ref<Material> material);

		virtual bool IsHit(const Ray& ray, float minT, float maxT, HitRecord& hitRecord) const override;

		glm::vec3 GetCenter(float time) const;
	private:
		glm::vec3 m_Center0, m_Center1;
		float m_Time0, m_Time1;
		float m_Radius;
		Ref<Material> m_MaterialPtr;
	};

}
