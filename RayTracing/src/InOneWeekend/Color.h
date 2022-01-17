#pragma once

#include <glm/vec3.hpp>

#include <ostream>

std::ostream& operator<<(std::ostream& out, glm::vec3& color)
{
	out << (int)(255.999f * color.r) << ' '
		<< (int)(255.999f * color.g) << ' '
		<< (int)(255.999f * color.b) << std::endl;

	return out;
}
