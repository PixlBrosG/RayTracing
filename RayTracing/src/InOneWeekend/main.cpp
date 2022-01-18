#include <iostream>

#include "Core/Base.h"

#include "InOneWeekend/RTWeekend.h"
#include "InOneWeekend/HittableList.h"
#include "InOneWeekend/Sphere.h"

namespace RayTracing {

	glm::vec3 GetRayColor(const Ray& ray, const Hittable& world)
	{
		HitRecord hitRecord;
		if (world.IsHit(ray, 0, infinity, hitRecord))
			return 0.5f * (hitRecord.Normal + 1.0f);

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

int main()
{
	using namespace RayTracing;

	// Initializing
	Log::Init();

	// Image
	constexpr float aspectRatio = 16.0f / 9.0f;
	constexpr int imageWidth = 400;
	constexpr int imageHeight = (int)(imageWidth / aspectRatio);

	// World
	HittableList world;
	world.Add(CreateRef<Sphere>(glm::vec3{ 0, 0, -1 }, 0.5f));
	world.Add(CreateRef<Sphere>(glm::vec3{ 0, -100.5f, -1 }, 100));

	// Camera
	float viewportHeight = 2.0f;
	float viewportWidth = aspectRatio * viewportHeight;
	float focalLength = 1.0f;

	glm::vec3 origin{ 0, 0, 0 };
	glm::vec3 horizontal{ viewportWidth, 0, 0 };
	glm::vec3 vertical{ 0, viewportHeight, 0 };
	glm::vec3 lowerLeftCorner = origin - horizontal / 2.0f - vertical / 2.0f - glm::vec3{ 0, 0, focalLength };

	// Render
	std::cout << "P3" << std::endl;
	std::cout << imageWidth << ' ' << imageHeight << std::endl;
	std::cout << 255 << std::endl;

	for (int y = imageHeight - 1; y >= 0; --y)
	{
		std::cerr << "\rScanlines remaining: " << y << "   " << std::flush;

		for (int x = 0; x < imageWidth; ++x)
		{
			float u = (float)x / (imageWidth - 1);
			float v = (float)y / (imageHeight - 1);

			Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical);
			glm::vec3 color = GetRayColor(ray, world);

			std::cout << color << std::endl;
		}
	}

	std::cerr << std::endl << "Done." << std::endl;

	return 0;

}

