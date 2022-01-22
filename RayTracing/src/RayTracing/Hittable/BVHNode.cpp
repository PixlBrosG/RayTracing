#include "RayTracing/Hittable/BVHNode.h"

#include <algorithm>
#include <iostream>

namespace RayTracing {

	BVHNode::BVHNode(const HittableList& list, float time0, float time1)
		: BVHNode(list.GetObjects(), 0, list.GetObjects().size(), time0, time1)
	{
	}

	BVHNode::BVHNode(const std::vector<Ref<Hittable>>& srcObjects, size_t start, size_t end, float time0, float time1)
	{
		// Create a modifiable array of the source scene objects
		std::vector<Ref<Hittable>> objects = srcObjects;

		int axis = Utils::RandomInt(0, 2);
		auto comparator = (axis == 0) ? Utils::CompareBoxX : (axis == 1) ? Utils::CompareBoxY : Utils::CompareBoxZ;

		size_t objectSpan = end - start;

		if (objectSpan == 1)
		{
			m_Left = m_Right = objects[start];
		}
		else if (objectSpan == 2)
		{
			if (comparator(objects[start], objects[start + 1]))
			{
				m_Left = objects[start];
				m_Right = objects[start + 1];
			}
			else
			{
				m_Left = objects[start + 1];
				m_Right = objects[start];
			}
		}
		else
		{
			std::sort(objects.begin() + start, objects.begin() + end, comparator);

			size_t mid = start + objectSpan / 2;
			m_Left = CreateRef<BVHNode>(objects, start, mid, time0, time1);
			m_Right = CreateRef<BVHNode>(objects, mid, end, time0, time1);
		}

		AABB boxLeft, boxRight;

		if (!m_Left->BoundingBox(time0, time1, boxLeft) ||
			!m_Right->BoundingBox(time0, time1, boxRight))
			std::cerr << "No bounding box in BVHNode constructor." << std::endl;

		m_Box = Utils::SurroundingBox(boxLeft, boxRight);
	}

	bool BVHNode::IsHit(const Ray& ray, float minT, float maxT, HitRecord& hitRecord) const
	{
		if (!m_Box.IsHit(ray, minT, maxT))
			return false;

		bool hitLeft = m_Left->IsHit(ray, minT, maxT, hitRecord);
		bool hitRight = m_Right->IsHit(ray, minT, hitLeft ? hitRecord.T : maxT, hitRecord);
		
		return hitLeft || hitRight;
	}

	bool BVHNode::BoundingBox(float time0, float time1, AABB& outputBox) const
	{
		outputBox = m_Box;
		return true;
	}

}
