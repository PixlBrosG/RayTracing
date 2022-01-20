#include "InOneWeekend/HittableList.h"

namespace RayTracing {

	HittableList::HittableList(Ref<Hittable> object)
	{
		Add(object);
	}

	bool HittableList::IsHit(const Ray& ray, float minT, float maxT, HitRecord& hitRecord) const
	{
		HitRecord tempRecord;
		bool hitAnything = false;
		float closestSoFar = maxT;

		for (Ref<Hittable> object : m_Objects)
		{
			if (object->IsHit(ray, minT, closestSoFar, tempRecord))
			{
				hitAnything = true;
				closestSoFar = tempRecord.T;
			}
		}

		if (hitAnything)
			hitRecord = tempRecord;

		return hitAnything;
	}

}
