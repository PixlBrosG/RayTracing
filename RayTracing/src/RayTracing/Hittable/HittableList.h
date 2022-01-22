#pragma once

#include <vector>

#include "RayTracing/Core/Base.h"

#include "RayTracing/Hittable/Hittable.h"

namespace RayTracing {

	class HittableList : public Hittable
	{
	public:
		HittableList() = default;
		HittableList(Ref<Hittable> object);

		const std::vector<Ref<Hittable>>& GetObjects() const { return m_Objects; }

		void Clear() { m_Objects.clear(); }
		void Add(Ref<Hittable> object) { m_Objects.push_back(object); }

		virtual bool IsHit(const Ray& ray, float minT, float maxT, HitRecord& hitRecord) const override;
		virtual bool BoundingBox(float time0, float time1, AABB& outputBox) const override;
	private:
		std::vector<Ref<Hittable>> m_Objects;
	};

}
