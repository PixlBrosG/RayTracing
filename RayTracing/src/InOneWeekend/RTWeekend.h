#pragma once

#include <limits>
#include <ostream>

// Common headers

#include <glm/trigonometric.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/vec3.hpp>

#include "InOneWeekend/Ray.h"
#include "InOneWeekend/Hittable.h"

// Constants

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.1415926535897932385f;

// Utility functions

namespace RayTracing { namespace Utils {

	float RandomFloat();
	float RandomFloat(float max);
	float RandomFloat(float min, float max);

	float Clamp(float x, float min, float max);

	glm::vec3 GetRayColor(const Ray& ray, const Hittable& world);
	void WriteColor(std::ostream& out, const glm::vec3& color, int samplesPerPixel);

} }
