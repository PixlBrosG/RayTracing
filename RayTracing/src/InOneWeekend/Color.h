#pragma once

#include <ostream>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "InOneWeekend/Ray.h"

namespace RayTracing {

	glm::vec3 GetRayColor(const Ray& ray)
	{
		glm::vec3 unitDirection = glm::normalize(ray.GetDirection());
		float t = 0.5f * (unitDirection.y + 1.0f);
		return (1.0f - t) * glm::vec3{ 1.0f, 1.0f, 1.0f } + t * glm::vec3{ 0.5f, 0.7f, 1.0f };
	}

}

std::ostream& operator<<(std::ostream& out, glm::vec3& color)
{
	out << (int)(255.999f * color.r) << ' '
		<< (int)(255.999f * color.g) << ' '
		<< (int)(255.999f * color.b);

	return out;
}
