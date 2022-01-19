#include "InOneWeekend/RTWeekend.h"

#include <random>

#include "InOneWeekend/Hittable.h"
#include "InOneWeekend/Materials/Material.h"

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
			Ray scattered;
			glm::vec3 attenuation;

			if (hitRecord.MaterialPtr->Scatter(ray, hitRecord, attenuation, scattered))
				return attenuation * GetRayColor(scattered, world, depth - 1);
			return glm::vec3{ 0, 0, 0 };
		}

		glm::vec3 unitDirection = glm::normalize(ray.GetDirection());
		float t = 0.5f * (unitDirection.y + 1.0f);
		return (1.0f - t) * glm::vec3(1.0f) + t * glm::vec3{0.5f, 0.7f, 1.0f};
	}

	void WriteColor(std::ostream& out, const glm::vec3& color, int samplesPerPixel)
	{
		// Divide the color by the number of samples
		float scale = 1.0f / samplesPerPixel;
		float r = glm::sqrt(color.r * scale);
		float g = glm::sqrt(color.g * scale);
		float b = glm::sqrt(color.b * scale);

		// Write the translated [0,255] value of each color component
//		out << (int)(256 * Clamp(r, 0.0f, 0.999f)) << ' '
//			<< (int)(256 * Clamp(g, 0.0f, 0.999f)) << ' '
//			<< (int)(256 * Clamp(b, 0.0f, 0.999f)) << std::endl;
	
		out << 255 * r << ' '
			<< 255 * g << ' '
			<< 255 * b << std::endl;
	}

	glm::vec3 RandomVec3()
	{
		return glm::vec3{ RandomFloat(), RandomFloat() , RandomFloat() };
	}

	glm::vec3 RandomVec3(float min, float max)
	{
		return glm::vec3{ RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max) };
	}

	glm::vec3 RandomInUnitDisk()
	{
		while (true)
		{
			glm::vec3 point = glm::vec3{ RandomFloat(-1, 1), RandomFloat(-1, 1), 0 };
			if (glm::length2(point) < 1)
				return point;
		}
	}

	glm::vec3 RandomInUnitSphere()
	{
		while (true)
		{
			glm::vec3 point = RandomVec3(-1, 1);
			if (glm::length2(point) < 1)
				return point;
		}
	}

	glm::vec3 RandomInHemiSphere(const glm::vec3& normal)
	{
		glm::vec3 inUnitSphere = RandomInUnitSphere();
		if (glm::dot(inUnitSphere, normal) > 0.0f) // In the hemisphere as the normal
			return inUnitSphere;
		else
			return -inUnitSphere;
	}
	
	glm::vec3 RandomUnitVector()
	{
		return glm::normalize(RandomInUnitSphere());
	}

	bool IsNearZero(const glm::vec3& vector)
	{
		constexpr float s = 1e-8f;
		return fabs(vector.x) < s &&
			   fabs(vector.y) < s &&
			   fabs(vector.z) < s;
	}

	glm::vec3 Reflect(const glm::vec3& v, const glm::vec3& n)
	{
		return v - 2 * glm::dot(v, n) * n;
	}

	glm::vec3 Refract(const glm::vec3& uv, const glm::vec3& n, float etaiOverEtat)
	{
		float cosTheta = fmin(glm::dot(-uv, n), 1.0f);
		glm::vec3 rayOutPerp = etaiOverEtat * (uv + cosTheta * n);
		glm::vec3 rayOutParalell = -glm::sqrt(fabs(1.0f - glm::length2(rayOutPerp))) * n;
		return rayOutPerp + rayOutParalell;
	}

} }
