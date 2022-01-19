#include <iostream>

#include "Core/Base.h"

#include "InOneWeekend/RTWeekend.h"
#include "InOneWeekend/HittableList.h"
#include "InOneWeekend/Sphere.h"
#include "InOneWeekend/Camera.h"

#include "InOneWeekend/Materials/Lambertian.h"
#include "InOneWeekend/Materials/Metal.h"
#include "InOneWeekend/Materials/Dielectric.h"

int main()
{
	using namespace RayTracing;

	// Initializing
	Log::Init();

	// Image
	constexpr float aspectRatio = 16.0f / 9.0f;
	constexpr int imageWidth = 400;
	constexpr int imageHeight = (int)(imageWidth / aspectRatio);
	constexpr int samplesPerPixel = 100;
	constexpr int maxDepth = 50;

	// World
	HittableList world;

	auto materialGround = CreateRef<Lambertian>(glm::vec3{ 0.8f, 0.8f, 0.0f });
	auto materialCenter = CreateRef<Lambertian>(glm::vec3{ 0.1f, 0.2f, 0.5f });
	auto materialLeft   = CreateRef<Dielectric>(1.5f);
	auto materialRight  = CreateRef<Metal>(glm::vec3{ 0.8f, 0.6f, 0.2f }, 0.0f);

	world.Add(CreateRef<Sphere>(glm::vec3{ -1.0f,    0.0f, -1.0f },   0.5f, materialLeft));
	world.Add(CreateRef<Sphere>(glm::vec3{ -1.0f,    0.0f, -1.0f },  -0.4f, materialLeft));
	world.Add(CreateRef<Sphere>(glm::vec3{  1.0f,    0.0f, -1.0f },   0.5f, materialRight));
	world.Add(CreateRef<Sphere>(glm::vec3{  0.0f, -100.5f, -1.0f }, 100.0f, materialGround));
	world.Add(CreateRef<Sphere>(glm::vec3{  0.0f,    0.0f, -1.0f },   0.5f, materialCenter));

	// Camera
	Camera camera;

	// Render
	std::cout << "P3" << std::endl;
	std::cout << imageWidth << ' ' << imageHeight << std::endl;
	std::cout << 255 << std::endl;

	for (int y = imageHeight - 1; y >= 0; --y)
	{
		std::cerr << "\rScanlines remaining: " << y << "   " << std::flush;

		for (int x = 0; x < imageWidth; ++x)
		{
			glm::vec3 color{ 0, 0, 0 };
			for (int s = 0; s < samplesPerPixel; ++s)
			{
				float u = (x + Utils::RandomFloat()) / (imageWidth - 1);
				float v = (y + Utils::RandomFloat()) / (imageHeight - 1);
				Ray ray = camera.GetRay(u, v);
				color += Utils::GetRayColor(ray, world, maxDepth);
			}
			Utils::WriteColor(std::cout, color, samplesPerPixel);
		}
	}

	std::cerr << std::endl << "Done." << std::endl;

	return 0;

}

