#include "RayTracing/Utils/RTUtils.h"

#include <random>
#include <iostream>

#include "RayTracing/Hittable/Hittable.h"
#include "RayTracing/Hittable/HittableList.h"

#include "RayTracing/Hittable/Sphere.h"
#include "RayTracing/Hittable/MovingSphere.h"

#include "RayTracing/Materials/Material.h"
#include "RayTracing/Materials/Lambertian.h"
#include "RayTracing/Materials/Metal.h"
#include "RayTracing/Materials/Dielectric.h"

#include "RayTracing/Ray.h"

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

	int RandomInt(int min, int max)
	{
		return (int)RandomFloat((float)min, (float)max + 1);
	}

	glm::vec3 GetRayColor(const Ray& ray, const Hittable& world, int depth)
	{
		if (depth <= 0)
			return glm::vec3(0);

		HitRecord hitRecord;
		if (world.IsHit(ray, 0.001f, infinity, hitRecord))
		{
			Ray scattered;
			glm::vec3 attenuation;

			if (hitRecord.MaterialPtr->Scatter(ray, hitRecord, attenuation, scattered))
				return attenuation * GetRayColor(scattered, world, depth - 1);
			return glm::vec3(0);
		}

		glm::vec3 unitDirection = glm::normalize(ray.GetDirection());
		float t = 0.5f * (unitDirection.y + 1.0f);
		return (1.0f - t) * glm::vec3(1.0f) + t * glm::vec3{ 0.5f, 0.7f, 1.0f };
	}

	glm::vec3 RandomVec3()
	{
		return glm::vec3{ RandomFloat(), RandomFloat() , RandomFloat() };
	}

	glm::vec3 RandomVec3(float min, float max)
	{
		return RandomVec3() * (max - min) + min;
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
		constexpr glm::vec3 s(1e-8f);
		return glm::all(glm::lessThan(glm::abs(vector), s));
	}

	glm::vec3 Reflect(const glm::vec3& v, const glm::vec3& n)
	{
		return v - 2 * glm::dot(v, n) * n;
	}

	glm::vec3 Refract(const glm::vec3& uv, const glm::vec3& n, float etaiOverEtat)
	{
		float cosTheta = glm::min(glm::dot(-uv, n), 1.0f);
		glm::vec3 rayOutPerp = etaiOverEtat * (uv + cosTheta * n);
		glm::vec3 rayOutParalell = -glm::sqrt(glm::abs(1.0f - glm::length2(rayOutPerp))) * n;
		return rayOutPerp + rayOutParalell;
	}

	HittableList RandomScene()
	{
		HittableList world;

		Ref<Lambertian> groundMaterial = CreateRef<Lambertian>(glm::vec3{ 0.5f, 0.5f, 0.5f });
		world.Add(CreateRef<Sphere>(glm::vec3{ 0, -1000, 0 }, 1000, groundMaterial));

		for (int a = -11; a < 11; ++a)
		{
			for (int b = -11; b < 11; ++b)
			{
				float chooseMat = RandomFloat();
				glm::vec3 center{ a + 0.9f * RandomFloat(), 0.2f, b + 0.9f * RandomFloat() };

				if (glm::length(center - glm::vec3{ 4, 0.2f, 0 }) > 0.9f)
				{
					Ref<Material> sphereMaterial;

					if (chooseMat < 0.8f)
					{
						// Diffuse
						glm::vec3 albedo = RandomVec3() * RandomVec3();
						sphereMaterial = CreateRef<Lambertian>(albedo);
						glm::vec3 center2 = center + glm::vec3{ 0, RandomFloat(0, 0.5f), 0 };
						world.Add(CreateRef<MovingSphere>(center, center2, 0.0f, 1.0f, 0.2f, sphereMaterial));
					}
					else if (chooseMat < 0.95f)
					{
						// Metal
						glm::vec3 albedo = RandomVec3(0.5f, 1.0f);
						float fuzz = RandomFloat(0.0f, 0.5f);
						sphereMaterial = CreateRef<Metal>(albedo, fuzz);
						world.Add(CreateRef<Sphere>(center, 0.2f, sphereMaterial));
					}
					else
					{
						// Glass
						sphereMaterial = CreateRef<Dielectric>(1.5f);
						world.Add(CreateRef<Sphere>(center, 0.2f, sphereMaterial));
					}
				}
			}
		}

		Ref<Dielectric> material1 = CreateRef<Dielectric>(1.5f);
		world.Add(CreateRef<Sphere>(glm::vec3{ 0, 1, 0 }, 1.0f, material1));
		
		Ref<Lambertian> material2 = CreateRef<Lambertian>(glm::vec3{ 0.4f, 0.2f, 0.1f });
		world.Add(CreateRef<Sphere>(glm::vec3{ -4, 1, 0 }, 1.0f, material2));
		

		Ref<Metal> material3 = CreateRef<Metal>(glm::vec3{ 0.7f, 0.6f, 0.5f }, 0.0f);
		world.Add(CreateRef<Sphere>(glm::vec3{ 4, 1, 0 }, 1.0f, material3));
		
		return world;
	}

	AABB SurroundingBox(const AABB& box0, const AABB& box1)
	{
		glm::vec3 small
		{
			glm::min(box0.GetMin().x, box1.GetMin().x),
			glm::min(box0.GetMin().y, box1.GetMin().y),
			glm::min(box0.GetMin().z, box1.GetMin().z)
		};

		glm::vec3 big
		{
			glm::min(box0.GetMax().x, box1.GetMax().x),
			glm::min(box0.GetMax().y, box1.GetMax().y),
			glm::min(box0.GetMax().z, box1.GetMax().z)
		};

		return AABB(small, big);
	}

	inline bool CompareBox(const Ref<Hittable> a, const Ref<Hittable> b, int axis)
	{
		AABB boxA, boxB;

		if (!a->BoundingBox(0, 0, boxA) || !b->BoundingBox(0, 0, boxB))
			std::cerr << "No bounding box in BVHNode constructor." << std::endl;

		return boxA.GetMin()[axis] < boxB.GetMin()[axis];
	}

	bool CompareBoxX(const Ref<Hittable> a, const Ref<Hittable> b) { return CompareBox(a, b, 0); }
	bool CompareBoxY(const Ref<Hittable> a, const Ref<Hittable> b) { return CompareBox(a, b, 1); }
	bool CompareBoxZ(const Ref<Hittable> a, const Ref<Hittable> b) { return CompareBox(a, b, 2); }

} }

std::ostream& operator<<(std::ostream& out, const glm::vec3& color)
{
	glm::vec3 clr = 255.0f * glm::sqrt(color);

	// Write the translated [0,255] value of each color component
	out << clr.r << ' '
		<< clr.g << ' '
		<< clr.b << std::endl;

	return out;
}
