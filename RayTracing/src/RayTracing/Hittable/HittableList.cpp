#include "RayTracing/Hittable/HittableList.h"

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

	bool HittableList::BoundingBox(float time0, float time1, AABB& outputBox) const
	{
		if (m_Objects.empty())
			return false;

		AABB tempBox;
		bool firstBox = true;

		for (const Ref<Hittable>& object : m_Objects)
		{
			if (!object->BoundingBox(time0, time1, tempBox))
				return false;
			outputBox = firstBox ? tempBox : Utils::SurroundingBox(outputBox, tempBox);
			firstBox = false;
		}

		return true;
	}

}
