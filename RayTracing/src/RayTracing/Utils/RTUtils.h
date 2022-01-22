#pragma once

#include <limits>
#include <ostream>

// Common headers

#include <glm/trigonometric.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/vec3.hpp>

#include "RayTracing/Core/Base.h"

// Constants

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.1415926535897932385f;

// Utility functions

namespace RayTracing {

	class Hittable;
	class HittableList;
	class AABB;
	class Ray;

	namespace Utils {

		float RandomFloat();
		float RandomFloat(float max);
		float RandomFloat(float min, float max);

		int RandomInt(int min, int max);

		glm::vec3 GetRayColor(const Ray& ray, const Hittable& world, int depth);

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

		AABB SurroundingBox(const AABB& box0, const AABB& box1);

		inline bool CompareBox(const Ref<Hittable> a, const Ref<Hittable> b, int axis);

		bool CompareBoxX(const Ref<Hittable> a, const Ref<Hittable> b);
		bool CompareBoxY(const Ref<Hittable> a, const Ref<Hittable> b);
		bool CompareBoxZ(const Ref<Hittable> a, const Ref<Hittable> b);

	}

}

std::ostream& operator<<(std::ostream& out, const glm::vec3& color);
