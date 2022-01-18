#include <iostream>

#include "Core/Base.h"

#include "InOneWeekend/RTWeekend.h"
#include "InOneWeekend/HittableList.h"
#include "InOneWeekend/Sphere.h"
#include "InOneWeekend/Camera.h"


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
	world.Add(CreateRef<Sphere>(glm::vec3{ 0, 0, -1 }, 0.5f));
	world.Add(CreateRef<Sphere>(glm::vec3{ 0, -100.5f, -1 }, 100));

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

