#include "InOneWeekend/RTWeekend.h"

#include <random>

namespace RayTracing { namespace Utils {

	float RandomFloat()
	{
		static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
		static std::mt19937 generator;
		return distribution(generator);
	}

	float RandomFloat(float max)
	{
		return RandomFloat() * max;
	}

	float RandomFloat(float min, float max)
	{
		return RandomFloat() * (max - min) + min;
	}

	float Clamp(float x, float min, float max)
	{
		return x < min ? min : (x > max ? max : x);
	}

	glm::vec3 GetRayColor(const Ray& ray, const Hittable& world, int depth)
	{
		if (depth <= 0)
			return glm::vec3{ 0, 0, 0 };

		HitRecord hitRecord;
		if (world.IsHit(ray, 0.001f, infinity, hitRecord))
		{
			glm::vec3 target = hitRecord.Normal + RandomInUnitSphere();
			return 0.5f * GetRayColor(Ray(hitRecord.Point, target), world, depth - 1);
		}

		glm::vec3 unitDirection = glm::normalize(ray.GetDirection());
		float t = 0.5f * (unitDirection.y + 1.0f);
		return (1.0f - t) * glm::vec3{ 1.0f, 1.0f, 1.0f } + t * glm::vec3{ 0.5f, 0.7f, 1.0f };
	}

	void WriteColor(std::ostream& out, const glm::vec3& color, int samplesPerPixel)
	{
		// Divide the color by the number of samples
		float scale = 1.0f / samplesPerPixel;
		float r = glm::sqrt(color.r * scale);
		float g = glm::sqrt(color.g * scale);
		float b = glm::sqrt(color.b * scale);

		// Write the translated [0,255] value of each color component
		out << (int)(256 * Clamp(r, 0.0f, 0.999f)) << ' '
			<< (int)(256 * Clamp(g, 0.0f, 0.999f)) << ' '
			<< (int)(256 * Clamp(b, 0.0f, 0.999f)) << std::endl;
	}

	glm::vec3 RandomVec3()
	{
		return glm::vec3{ RandomFloat(), RandomFloat() , RandomFloat() };
	}

	glm::vec3 RandomVec3(float min, float max)
	{
		return glm::vec3{ RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max) };
	}

	glm::vec3 RandomInUnitSphere()
	{
		while (true)
		{
			glm::vec3 point = RandomVec3(-1, 1);
//			if (glm::length2(point) < 1)
			if (glm::length(point) < 1)
				return point;
		}
	}

} }
