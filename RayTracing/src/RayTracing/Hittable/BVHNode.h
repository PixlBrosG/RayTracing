#pragma once

#include "RayTracing/Utils/RTUtils.h"

#include "RayTracing/Hittable/Hittable.h"
#include "RayTracing/Hittable/HittableList.h"

namespace RayTracing {

	class BVHNode : public Hittable
	{
	public:
		BVHNode() = default;

		BVHNode(const HittableList& list, float time0, float time1);
		BVHNode(const std::vector<Ref<Hittable>>& srcObjects, size_t start, size_t end, float time0, float time1);

		virtual bool IsHit(const Ray& ray, float minT, float maxT, HitRecord& hitRecord) const override;
		virtual bool BoundingBox(float time0, float time1, AABB& outputBox) const override;
	private:
		Ref<Hittable> m_Left, m_Right;
		AABB m_Box;
	};

}
