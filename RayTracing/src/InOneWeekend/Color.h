#pragma once

#include <ostream>

#include <glm/vec3.hpp>

std::ostream& operator<<(std::ostream& out, glm::vec3& color)
{
	out << (int)(255.999f * color.r) << ' '
		<< (int)(255.999f * color.g) << ' '
		<< (int)(255.999f * color.b);

	return out;
}
