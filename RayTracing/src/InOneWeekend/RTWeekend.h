#pragma once

#include <limits>
#include <ostream>

// Common headers

#include <glm/trigonometric.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/vec3.hpp>

#include "InOneWeekend/Ray.h"

// Constants

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.1415926535897932385f;

// Utility functions

namespace RayTracing {

	class Hittable;
	class HittableList;

	namespace Utils {

		float RandomFloat();
		float RandomFloat(float max);
		float RandomFloat(float min, float max);

		float Clamp(float x, float min, float max);

		glm::vec3 GetRayColor(const Ray& ray, const Hittable& world, int depth);
		void WriteColor(std::ostream& out, const glm::vec3& color, int samplesPerPixel);

		glm::vec3 RandomVec3();
		glm::vec3 RandomVec3(float min, float max);

		glm::vec3 RandomInUnitDisk();
		glm::vec3 RandomInUnitSphere();
		glm::vec3 RandomInHemiSphere(const glm::vec3& normal);
		glm::vec3 RandomUnitVector();

		bool IsNearZero(const glm::vec3& vector);

		glm::vec3 Reflect(const glm::vec3& v, const glm::vec3& n);
		glm::vec3 Refract(const glm::vec3& uv, const glm::vec3& n, float etaiOverEtat);

		HittableList RandomScene();

	}

}
