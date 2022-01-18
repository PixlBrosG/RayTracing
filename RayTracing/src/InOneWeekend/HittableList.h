#pragma once

#include <vector>

#include "Core/Base.h"

#include "InOneWeekend/Hittable.h"

namespace RayTracing {

	class HittableList : public Hittable
	{
	public:
		HittableList() = default;
		HittableList(Ref<Hittable> object);

		void Clear() { m_Objects.clear(); }
		void Add(Ref<Hittable> object) { m_Objects.push_back(object); }

		virtual bool IsHit(const Ray& ray, float minT, float maxT, HitRecord& hitRecord) const override;
	private:
		std::vector<Ref<Hittable>> m_Objects;
	};

}
